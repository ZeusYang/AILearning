#include <iostream>  
#include <string.h>  
#include <fstream>  
#include <iterator>  
#include <algorithm>  
#include <limits.h>  
#include <math.h>  
#include <stdlib.h>  
#include <ctime>
#include <vector>
#include <map>

using namespace std;

const int nCities = 130; //城市数量  
double length_table[nCities][nCities];//存储各点间距离
const int group_size = 500;
const int time_to_breed = 8000;
const double p_cross = 0.8;
double p_varia = 0.5;//像模拟退火那样动态改变变异率

struct node
{
	int num;
	double x;
	double y;
}nodes[nCities];

class GenbyOne {
public:
	GenbyOne(int _seed = -1) : seed(_seed) {}
	int operator() () { return seed += 1; }
private:
	int seed;
};

void init_dis() // create matrix to storage the Distance each city  
{
	int i, j;
	ifstream in("ch130.txt");
	for (i = 0; i < nCities; i++)
	{
		in >> nodes[i].num >> nodes[i].x >> nodes[i].y;
	}

	for (i = 0; i < nCities; i++)
	{
		length_table[i][i] = (double)INT_MAX;
		for (j = i + 1; j < nCities; j++)
		{
			length_table[i][j] = length_table[j][i] = sqrt(
				(nodes[i].x - nodes[j].x) * (nodes[i].x - nodes[j].x) +
				(nodes[i].y - nodes[j].y) * (nodes[i].y - nodes[j].y));
		}
	}
}



class way //一条路径  
{
public:
	void Calculate_length() {
		length = 0;
		//遍历path
		for (int i = 1; i < nCities; i++) {
			length += length_table[path[i - 1] - 1][path[i] - 1];
			//cout << length << endl;
		}
		length += length_table[path[nCities - 1] - 1][path[0] - 1];
	}

	way() {
		length = 0;
		generate(path, path + nCities, GenbyOne(0));//自动生成形如0，1，2，3的编号序列
		random_shuffle(path, path + nCities);//将序列随机打乱作为初始路径
		Calculate_length();
	}//以随机序列初始化

	double length;//代价，总长度  
	int path[nCities];//路径
	
	/*void getNewSolution_cross(way &t) {//使用均匀交叉(效果并不好)
		double pick;
		for (int i = 0; i < nCities; i++) {
			pick = ((double)rand()) / RAND_MAX;
			if (pick > 0.5) {
				int temp = t.path[i];
				t.path[i] = path[i];
				path[i] = temp;
			}
		}
		int i = 0; int j = 0;
		bool count_dup_1[nCities + 1] = { false };
		bool count_dup_2[nCities + 1] = { false };
		while (i < nCities && j < nCities) {
			if (count_dup_1[path[i]] && count_dup_2[t.path[j]]) {
				int temp = path[i];
				path[i] = t.path[j];
				t.path[j] = temp;
				i++;
				j++;
			}
			if (i >= 130 || j >= 130)
				break;
			if (!count_dup_1[path[i]]) {
				count_dup_1[path[i]] = true;
				i++;
			}
			if (!count_dup_2[t.path[j]]) {
				count_dup_2[t.path[j]] = true;
				j++;
			}
		}

		t.Calculate_length();
		Calculate_length();
	}*/

	void getNewSolution_cross(way &t) {
		//因此改用单点交叉
		int mark = rand() % (nCities - 2) + 1;//1 to nCities - 2
		for (int i = mark; i < nCities; i++) {
			int temp = path[i];
			path[i] = t.path[i];
			t.path[i] = temp;
		}

		int i = 0; int j = 0;
		bool count_dup_1[nCities + 1] = { false };
		bool count_dup_2[nCities + 1] = { false };
		while (i < nCities && j < nCities) {
			if (count_dup_1[path[i]] && count_dup_2[t.path[j]]) {
				int temp = path[i];
				path[i] = t.path[j];
				t.path[j] = temp;
				i++;
				j++;
			}
			if (i >= 130 || j >= 130)
				break;
			if (!count_dup_1[path[i]]) {
				count_dup_1[path[i]] = true;
				i++;
			}
			if (!count_dup_2[t.path[j]]) {
				count_dup_2[t.path[j]] = true;
				j++;
			}
		}
		Calculate_length();
		t.Calculate_length();
	}

	void getNewSolution_varia() {//模拟退火中的代码，用来做变异操作
		int i = rand() % nCities;
		int j = rand() % nCities;
		if (i > j) {
			swap(i, j);
		}
		else if (i == j)return;
		//随机取路径中两点进行操作

		int choose = rand() % 3;
		switch (choose) {
		case 0:
			swap(path[i], path[j]); break;
		case 1:
			reverse(path + i, path + j); break;
		default:
			if (j == (nCities - 1)) return;
			rotate(path + i, path + j, path + j + 1);
		}
		Calculate_length();
	}


};

vector<way> group;//种群，大小为group_size

void init(void) {
	for (int i = 0; i < group_size; i++) {
		group.push_back(way());
	}
}// 种群初始化函数

void choose(vector<way> & group){
	double sum_fitness = 0;
	double fitness[group_size];//适应性数组
	double chance[group_size];//概率数组
	double pick;//用于轮盘赌的随机数
	vector<way> next;

	for (int i = 0; i < group_size; i++) {
		fitness[i] = 1 / group[i].length;
		sum_fitness += fitness[i];
	}
	for (int i = 0; i < group_size; i++) {
		chance[i] = fitness[i] / sum_fitness;
	}
	//轮盘赌
	for (int i = 0; i < group_size; i++) {
		pick = ((double)rand()) / RAND_MAX;//0到1的随机数
		for (int j = 0; j < group_size; j++) {
			pick -= chance[j];
			if (pick <= 0) {
				next.push_back(group[j]);
				break;
			}
			if (j == group_size - 1) {
				next.push_back(group[j]);
			}
		}
	}
	group = next;
}

void cross(vector<way> & group) {
	int point = 0;
	int choice1, choice2;
	while (point < group_size/*防止越界*/) {
		double pick = ((double)rand()) / RAND_MAX;//0到1的随机数
		if (pick > p_cross)
			continue;//判断是否交叉
		else {
			choice1 = point;
			choice2 = point + 1;
			group[choice1].getNewSolution_cross(group[choice2]);//交叉
			//接下来将交叉后的路径合法化
/*
			int i = 0; int j = 0;
			bool count_dup_1[nCities + 1] = {false};
			bool count_dup_2[nCities + 1] = {false};
			while (i < nCities && j < nCities) {
				if (count_dup_1[group[choice1].path[i]] && count_dup_2[group[choice2].path[j]]) {
					int temp = group[choice1].path[i];
					group[choice1].path[i] = group[choice2].path[j];
					group[choice2].path[j] = temp;
					i++;
					j++;
				}
				if (i >= 130 || j >= 130)
					break;
				if (!count_dup_1[group[choice1].path[i]]) {
					count_dup_1[group[choice1].path[i]] = true;
					i++;
				}
				if (!count_dup_2[group[choice2].path[j]]) {
					count_dup_2[group[choice2].path[j]] = true;
					j++;
				}
			}
*/
		}
		point += 2;
	}
}

void varia(vector<way> & group) {//变异
	int point = 0;
	while (point < group_size) {
		double pick = ((double)rand()) / RAND_MAX;//0到1的随机数
		if (pick < p_varia) {
			group[point].getNewSolution_varia();
		}
		point++;
	}
}

void judge(vector<way> & old_group, vector<way> & group) {//决定子代是否能取代亲本
	
	int point = 0;
	
	while (point < group_size) {
		if (old_group[point].length < group[point].length)
			group[point] = old_group[point];
		point++;
	}
}

way GA() {
	time_t start, finish;
	start = clock(); // 开始计时
	srand((unsigned)time(NULL)); // 初始化随机数种子
	init(); // 初始化种群

	way best;


	for (int i = 0; i < time_to_breed; i++) {
		vector<way> old_group = group;
		
		choose(group);
		cross(group);
		for(int other = 0;other < 5;other++){
			varia(group);
			judge(old_group,group);
		}
		//varia(group);
		//judge(old_group, group);
		for (int j = 0; j < group_size; j++) {
			if (group[j].length < best.length){
				best = group[j];
				cout << i << "->>" << best.length << endl;
			}
		}
	}

	return best;
}

int main() {//测试
	//实际程序
	init_dis();//初始化各点距离
	way ans = GA();
	//srand((unsigned)time(NULL)); // 初始化随机数种子
	//init();
	//choose(group);
	cout << ans.length << endl <<"------------------------------"<<endl;
	bool count[nCities] = {false};
	for (int i = 0; i < nCities; i++) {
		cout << ans.path[i] << " -> ";
	}
	cout << endl;

}

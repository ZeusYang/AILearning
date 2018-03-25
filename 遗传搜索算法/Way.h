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


class GenbyOne {
public:
	GenbyOne(int _seed = -1) : seed(_seed) {}
	int operator() () { return seed += 1; }
private:
	int seed;
};

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

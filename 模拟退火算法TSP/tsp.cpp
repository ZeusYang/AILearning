#include <fstream>  
#include <iterator>  
#include <algorithm>  
#include <limits.h>  
#include <iostream>
#include <math.h>  
#include <stdlib.h>  
#include <ctime>
#include <vector>
using namespace std;

const int nCities = 130; //城市数量  
const double SPEED = 0.98;//退火速度  
const int INITIAL_TEMP = 1000;//初始温度  
							 

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

double length_table[nCities][nCities];//存储各点间距离
vector<double> balance;

class answer //一个解  
{
public:
	answer() {
		length = 0;
		generate(path, path + nCities, GenbyOne(0));//自动生成形如0，1，2，3的编号序列
		random_shuffle(path, path + nCities);//将序列随机打乱作为初始路径
		Calculate_length();
		//cout << " length->" << length;
	}

	void Calculate_length() {
		length = 0;
		//遍历path
		for (int i = 1; i < nCities; i++) {
			length += length_table[path[i - 1] - 1][path[i] - 1];
			//cout << length << endl;
		}
		length += length_table[path[nCities - 1] - 1][path[0] - 1];
	}

	double length;//代价，总长度  
	int path[nCities];//路径  
	bool operator < (const  answer &other) const
	{
		return length < other.length;
	}
};


//answer bestone = { INT_MAX,{ 0 } };//最优解  


void init_dis(); // create matrix to storage the Distance each city  
				 //answer SA_TSP(bool is_SA);
				 //void CalCulate_length(answer &t);//计算长度  
void print(answer &p);//打印一个解  
void getNewSolution(answer &t);// 从邻域中获去一个新解  
bool Accept(answer &bestone, answer &temp, double t);//新解以Metropolis 准则接受


void print(answer &p){
	int i;
	cout << "cost:" << p.length << endl;
	cout << "path:" ;
	for(i = 0;i < nCities;i ++){
		cout << p.path[i] << " ";
	} 
	cout << endl;
	for(i = 0;i < nCities;i ++){
		cout << nodes[p.path[i]-1].x << "," << nodes[p.path[i]-1].y << " ";
	}
	cout << endl;
}

double genInitialTemp(){
	 srand(time(NULL));
	 int numStatus = rand()%50+50;
	 double minLength = INT_MAX;
	 double maxLength = INT_MIN;
	 for(int x = 0;x < numStatus;x ++){
	 	answer temp;
	 	minLength = (minLength > temp.length)?temp.length:minLength;
	 	maxLength = (maxLength < temp.length)?temp.length:maxLength;
	 }
	 double delta = maxLength - minLength;
 	 double p = 0.8;
	 double result = 0.0;
	 result = -delta/(log(1.0/p - 1.0));
	 return result;
}


answer SA_TSP(bool is_SA) {
	srand(time(0));//之后用到很多随机数，设定种子
	int i = 0;
	double r = SPEED;
	double t = genInitialTemp();
	const double t_min = 0.01;

	answer temp;
	answer best = temp;
	while (t > t_min) {
		//设定一个固定的循环次数
		int L = 100 * nCities;
		for (i = 0; i < L; i++) {
			answer next = temp;
			getNewSolution(next);
			if (Accept(next, temp, t)) {
				temp = next;//接受新解为当前最优
				if(next < best){
					best = next;
				}
			}
		}
		t *= r;//降温
	}
	return best;
}

void getNewSolution(answer &t) {
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
		swap(t.path[i], t.path[j]); break;
	case 1:
		reverse(t.path + i, t.path + j); break;
	default:
		if (j == (nCities - 1)) return;
		rotate(t.path + i, t.path + j, t.path + j + 1);
	}
	t.Calculate_length();
}

bool Accept(answer &temp, answer &best, double t) {
	if (temp.length < best.length) return true;
	//else if ((int)(exp((best.length - temp.length) / t) * 100) > (rand() % 101))
	else if (rand() / (double)RAND_MAX < 1 / (1 + exp(-(best.length - temp.length) / t)))
		return true;

	return false;
}

void init_dis() // create matrix to storage the Distance each city  
{
	int i, j;
	ifstream in("ch130.txt");
	for (i = 0; i < nCities; i++)
	{
		in >> nodes[i].num >> nodes[i].x >> nodes[i].y;
		//cout << nodes[i].num << " " << nodes[i].x << " " << nodes[i].y << endl;
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

int main(int argc, char *argv[])
{
	init_dis();
	answer bestone = SA_TSP(true);
	print(bestone);
	cout << endl << bestone.length << endl;
	cout << "The gap between the optimal method:" << ((bestone.length - 6110)/6110) << endl; 
	//int x[1000], y[1000];

	return 0;
}

#include "Way.h"

const int group_size = 500;
const int time_to_breed = 8000;
const double p_cross = 0.8;
double p_varia = 0.5;//像模拟退火那样动态改变变异率

class GeneticAlgorithm{
public:
	struct node{
		int num;
		double x;
		double y;
	}nodes[nCities];
	
	vector<way> group;//种群，大小为group_size

	void init_dis();
	
	GeneticAlgorithm();
	
	~GeneticAlgorithm();

	way GA();

private:
	
	void choose(vector<way>& group);
	
	void cross(vector<way>& group);

	void varia(vector<way>& group);

	void judge(vector<way> & old_group, vector<way> & group);

	void init();
};

GeneticAlgorithm::GeneticAlgorithm(){
}

GeneticAlgorithm::~GeneticAlgorithm(){
	group.clear();
}

void GeneticAlgorithm::init(){
	group.resize(group_size,way());	
}

void GeneticAlgorithm::init_dis() // create matrix to storage the Distance each city  
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

void GeneticAlgorithm::choose(vector<way> & group){
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

void GeneticAlgorithm::cross(vector<way> & group) {
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
		}
		point += 2;
	}
}

void GeneticAlgorithm::varia(vector<way> & group) {//变异
	int point = 0;
	while (point < group_size) {
		double pick = ((double)rand()) / RAND_MAX;//0到1的随机数
		if (pick < p_varia) {
			group[point].getNewSolution_varia();
		}
		point++;
	}
}

void GeneticAlgorithm::judge(vector<way> & old_group, vector<way> & group) {//决定子代是否能取代亲本
	
	int point = 0;
	
	while (point < group_size) {
		if (old_group[point].length < group[point].length)
			group[point] = old_group[point];
		point++;
	}
}

way GeneticAlgorithm::GA() {
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
		for (int j = 0; j < group_size; j++) {
			if (group[j].length < best.length){
				best = group[j];
				cout << i << "->>" << best.length << endl;
			}
		}
	}

	return best;
}

int main() {
	GeneticAlgorithm process;
	process.init_dis();
	way ans = process.GA();
	cout << ans.length << endl <<"------------------------------"<<endl;
	bool count[nCities] = {false};
	for (int i = 0; i < nCities; i++) {
		cout << ans.path[i] << " -> ";
	}
	cout << endl;
}

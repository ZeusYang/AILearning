#ifndef NSGA_2_H
#define NSGA_2_H
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <ctime>
#define INFINIT 0xffffffff
using namespace std;
/***********************
 * NSGA-2 mop algortihm
 ***********************/
namespace NSGA_II {
const double PI = 3.1415926535898;

//NSGA-II parameters
int numObjective = 2;
double lowerBound = 0.0;
double upperBound = 1.0;
int dimension = 3;
int populationSize = 100;
int generationSize = 500;

//DE parameters
double CR = 1.0;
double F = 0.5;
double H = 20; //η
double pm = 1.0 / dimension;

vector<vector<double> > populationfValue(numObjective, vector<double>(2 * populationSize));
vector<double> fMax(numObjective,numeric_limits<double>::min());
vector<double> fMin(numObjective,numeric_limits<double>::max());

double gx(vector<double> x);
double f(int index, vector<double> x, int dimension);
double Fx(vector<double> x);


bool dominatedCompare(int p, int q, int dimension);
vector<vector<int> > fast_non_dominated_sort(vector<vector<double> >& P, int size, int dimension);//以下标的方式返回种群P的前沿面
vector<double> crowding_distance_assignment(vector<int>& I, int size);
void make_new_generation_DE(vector<vector<double> >& parent, int size, vector<vector<double> >& offspring);
void NSGA_II();

double gx(vector<double> x)
{
    double result = 0.0;
    for (int i = 0; i<numObjective; i++)
        result += pow(x[i] - 0.5, 2.0);

    return result;
}

//单目标：f（index）指目标index的函数f
double f(int index, vector<double> x, int dimension)
{
    int M = numObjective;
    double result;
    result = 1 + gx(x);

    for (int i = 0; i<M - index - 1; i++) {
        result *= cos(pow(x[i], PI)*PI / 2);
    }
    if (index>0)
        result *= sin(pow(x[M - index - 1], PI)*PI / 2);

    return result;
}

//多目标优化函数 min F=f1+f2+f3+……
double Fx(vector<double> x)
{
    double result = 0;
    for (int i = 0; i<numObjective; i++)
        result += f(i, x, dimension);
    return result;
}

//支配关系确定函数
bool dominatedCompare(int p, int q, int dimension)
{
    bool LE = true; //less or equal
    bool L = false; //less
    for (int i = 0; i<numObjective; i++) {
        if (populationfValue[i][p] > populationfValue[i][q]) LE = false;
        if (populationfValue[i][p] < populationfValue[i][q]) L = true;
    }
    return LE&&L;
}

//F[i]表示第i个前沿面的个体在P中的下标
vector<vector<int> > fast_non_dominated_sort(vector<vector<double> >& P, int size, int dimension)
{
    vector<vector<int> > S(size);
    vector<int> n(size, 0);
    vector<int> rank(size);
    vector<vector<int> > F(1);
    //对种群每个个体i和其他个体j确定支配关系，如果i对j存在支配关系，
    //则把其加入到其支配个体集合S[i]中
    //如果个体j对其（i）存在支配关系，则支配i的个体总数n[i]加一
    for (int i = 0; i<size; i++) {
        for (int j = 0; j<size; j++) {
            if (i != j) {
                if (dominatedCompare(i, j, dimension)) {
                    S[i].push_back(j);
                }
                else if (dominatedCompare(j, i, dimension)) {
                    n[i] ++;
                }
            }
        }
        //如果没有个体支配i，则i的排名为1并将其加入第一前沿面中
        if (n[i] == 0) {
            rank[i] = 1;
            F[0].push_back(i);
        }
    }

    //对每个前沿面的个体，将其加入其所属的第i前沿面中，并把受其支配的个体的受支配数n减1
    int i = 0;
    while (true) {
        vector<int> Q;
        for (int j = 0; j<F[i].size(); j++) {
            int p=F[i][j];
            for (int q = 0; q<S[p].size(); q++) {
                n[S[p][q]]--;
                if (n[S[p][q]] == 0) {
                    rank[S[p][q]] = i + 2;
                    Q.push_back(S[p][q]);
                }
            }
        }
        i += 1;
        if (Q.size()>0) {
            F.push_back(Q);
        }
        else {
            break;
        }
    }
    return F;
}

//进行需要计算拥挤距离的个体按照目标m依照fm的大小进行排序的辅助结构体
struct assist {
    int index;
    int objective;

    assist(int i, int m) {
        index = i;
        objective = m;
    }
};

//需要计算拥挤距离的个体按照目标m依照fm的大小进行排序 需要用到的比较器
bool myCmp(assist p, assist q)
{
    return populationfValue[p.objective][p.index]
            < populationfValue[q.objective][q.index];
}

//拥挤比较方法：I为父代、子代合并种群R中需要比较的个体的下标 ，size为I的大小
vector<double> crowding_distance_assignment(vector<int>& I, int size)
{
    //声明拥挤距离
    vector<double> distance(2 * populationSize, 0);

    for (int m = 0; m<numObjective; m++) {
        //对需要计算拥挤距离的个体按照目标m依照fm的大小进行排序
        vector<assist> ass;
        for (int i = 0; i<size; i++)
            ass.push_back(assist(I[i], m));
        sort(ass.begin(), ass.end(), myCmp);

        //将首尾两个个体的拥挤距离定义为无穷大
        distance[ass[0].index] = numeric_limits<double>::max();
        distance[ass[size - 1].index] = numeric_limits<double>::max();
        //对中间的个体计算其拥挤距离
        for (int i = 1; i<size - 1; i++) {
            distance[ass[i].index] = distance[ass[i].index] + (populationfValue[m][ass[i + 1].index]
                    - populationfValue[m][ass[i - 1].index]) / (fMax[m] - fMin[m]);

        }

    }
    //cout << "crowding_distance_assignment finish " << endl;
    return distance;
}

//对父代和子代的解的优劣进行排序的比较器
bool cmp(vector<double> p, vector<double> q)
{
    return Fx(p) < Fx(q);
}

//DE方法产生新解
void make_new_generation_DE(vector<vector<double> >& parent, int size, vector<vector<double> >& offspring)
{
    for (int i = 0; i<size; i++) {
        //Step 1.1 Select three solutions , from parent by using binary tournament selection
        //选择
        vector<bool> selected(size, false);
        int p[3];
        for (int k = 0; k<3; k++) {
            int r1 = rand() % size;
            int r2 = rand() % size;
            int r = Fx(parent[r1])<Fx(parent[r2]) ? r1 : r2;
            if (selected[r] == false) {
                selected[r] = true;
                p[k] = r;
            }
            else
                k--;
        }

        //Step 1.2
        //交叉
        vector<double> y(dimension);
        for (int k = 0; k<dimension; k++) {
            if (((rand() % 100) / 100.0) <= CR)
                y[k] = parent[p[0]][k] + F*(parent[p[1]][k] - parent[p[2]][k]);
            else
                y[k] = parent[p[0]][k];
        }

        for (int k = 0; k<dimension; k++) {
            if (((rand() % 100) / 100.0) <= pm) {
                double r = (rand() % 100) / 100.0;
                double dk;
                if (r<0.5)
                    dk = pow(2 * r, 1.0 / (1 + H)) - 1;
                else
                    dk = 1 - pow((2 - 2 * r), 1.0 / (1 + H));

                y[k] = y[k] + dk*(upperBound - lowerBound);
            }
        }

        //Step 1.3
        for (int k = 0; k<dimension; k++)
            if (y[k]<0.0 || y[k]>1.0)
                y[k] = (rand() % 100) / 100.0;

        offspring[i] = y;
    }

    //Step 2
    vector<vector<double> > P(2 * size, vector<double>(dimension, 0));
    for (int i = 0; i<size; i++)
        for (int j = 0; j<dimension; j++) {
            P[i][j] = parent[i][j];
            P[i + size][j] = offspring[i][j];
        }

    sort(P.begin(), P.end(), cmp);

    for (int i = 0; i<size; i++)
        for (int j = 0; j<dimension; j++)
            offspring[i][j] = P[i][j];

    //cout << "make_new_generation_DE finish" << endl;
}


//用于拥挤距离辅助排序的结构体
struct Idistance {
    int index;
    double distance;

    Idistance(int i, double d) {
        index = i;
        distance = d;
    }
};

//比较器
bool cmpD(Idistance p, Idistance q)
{
    return p.distance > q.distance;
}

void NSGA_II()
{
    //初始化种群
    vector<vector<double> > P(populationSize, vector<double>(dimension));
    for (int i = 0; i<populationSize; i++)
        for (int j = 0; j<dimension; j++)
            P[i][j] = (rand() % 100) / 100.0;

    vector<vector<double> > Q(populationSize, vector<double>(dimension));
    vector<vector<double> > R(2 * populationSize, vector<double>(dimension));

    //循环generationSize代 P
    for (int i = 0; i<generationSize; i++) {
        //使用DE算法产生子代 Q
        make_new_generation_DE(P, populationSize, Q);

        //将子代和父代合并为R进行选择
        for (int s = 0; s<populationSize; s++)
            for (int t = 0; t<dimension; t++) {
                R[s][t] = P[s][t];
                R[s + populationSize][t] = Q[s][t];
            }

        //计算 R中每个个体k在目标j中的值
        //计算每个目标当前为止的最大值和最小值
        for (int j = 0; j<numObjective; j++) {
            for (int k = 0; k<2 * populationSize; k++) {
                populationfValue[j][k] = f(j, R[k], dimension);
                fMax[j] = fMax[j]>populationfValue[j][k]?fMax[j]:populationfValue[j][k];
                fMin[j] = fMin[j]<populationfValue[j][k]?fMin[j]:populationfValue[j][k];
            }
        }

        //使用快速非支配排序算法将R中的个体划分为不同等级；
        //其中F[i]中表示等级为i+1的个体在R中的下标
        vector<vector<int> > F = fast_non_dominated_sort(R, 2 * populationSize, dimension);

        //选择排名靠前的个体作为新的种群
        int Psize = 0;
        int s = 0;
        while (Psize + F[s].size()<populationSize) {
            for (int j = 0; j<F[s].size(); j++)
                for (int k = 0; k<dimension; k++)
                    P[Psize + j][k] = R[F[s][j]][k];

            Psize += F[s].size();
            s++;
        }

        //此时F[s]为R中同一等级的个体，如果全部选择的话就会超过种群大小，所以需要计算拥挤距离进行选择
        //使用拥挤比较方法计算R中下标在F[s]中的个体的拥挤距离
        vector<double> distance = crowding_distance_assignment(F[s], F[s].size());
        //对R中下标在F[s]中的个体进行拥挤距离的降序排序
        vector<Idistance> tmp;
        for (int j = 0; j<F[s].size(); j++)
            tmp.push_back(Idistance(F[s][j], distance[F[s][j]]));
        sort(tmp.begin(), tmp.end(), cmpD);

        //选择拥挤距离大的个体作为新的种群
        for (int j = Psize; j<populationSize; j++)
            for (int k = 0; k<dimension; k++)
                P[j][k] = R[tmp[j - Psize].index][k];

    }

    //输出最终种群的优化结果F(x)
    for (int i = 0; i<populationSize; i++)
        cout << Fx(P[i]) << " ";
    //输出最终种群在每个目标上的优化结果
    for (int i = 0; i<2 * populationSize; i++) {
        cout << "(";
        for (int k = 0; k<numObjective - 1; k++)
            cout << populationfValue[k][i] << ",";
        cout << populationfValue[numObjective - 1][i] << ")" << endl;
    }
}
}
#endif // NSGA_2_H

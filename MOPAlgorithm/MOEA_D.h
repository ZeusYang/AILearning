#ifndef MOEA_D_H
#define MOEA_D_H
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <ctime>
using namespace std;

namespace MOEA_D {
const double PI = 3.1415926535898;

//MOEA/D parameters
int numObjective = 2;
double lowerBound = 0.0;
double upperBound = 1.0;
int dimension = 3;
int populationSize = 300;
int generationSize = 500;

double Delte=0.9; //δ:the probability that parent solutions are selected from the neighborhood
double nr=2; //the maximal number of solutions replaced by each child solution.
int T=20; //T closest weight vectors to each weight vector

//DE parameters
double CR = 1.0;
double F = 0.5;
double H = 20; //η
double pm = 1.0 / dimension;

// 全局变量
vector<vector<double> > population(populationSize,vector<double>(dimension,0.0));
vector<double> FV(populationSize,0.0);  //FV[i] = F(x[i])
vector<double> z(numObjective,0.0);  //z[i] the best value found so far for objective fi
vector<vector<double> > lambda(populationSize,vector<double>(numObjective,0.0)); //权值矩阵
vector<vector<int> > WVneighbors(populationSize,vector<int>(T,0)); //权值向量的邻居下标
vector<vector<double> > populationfValue(numObjective, vector<double>(2 * populationSize));

double gx(vector<double> x);
double fx(int index, vector<double> x, int dimension);
double Fx(vector<double> x);

void WVneighborInit();
void weightVectorGenerator();
double eularDistance(vector<double> x, vector<double> y);
void populationInit();
vector<double> make_new_solution_DE(int r1, int r2, int r3);
double subproblemValue(int index, vector<double> x);
void updateThePopulation();
void MOEA_D();

double gx(vector<double> x)
{
    double result = 0.0;
    for (int i = 0; i<numObjective; i++)
        result += pow(x[i] - 0.5, 2.0);

    return result;
}

//单目标：f（index）指目标index的函数f
double fx(int index, vector<double> x, int dimension)
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
        result += fx(i, x, dimension);
    return result;
}

void weightVectorGenerator()
{
    //cout << lambda.size() << endl;
    for(int i=0;i<populationSize;i++){
        double sum = 0;
        for(int j=0;j<numObjective;j++){
            lambda[i][j] = (rand() % 100) / 100.0;
            sum += lambda[i][j];
        }
        for(int j=0;j<numObjective;j++){
            lambda[i][j] = lambda[i][j] / sum;
        }
        //cout << i << endl;
    }
    //cout << "weightVectorGenerator" << endl;
    WVneighborInit();
}

double eularDistance(vector<double> x, vector<double> y, int size)
{
    double distance=0;
    for(int i=0;i<size;i++)
        distance += (x[i]-y[i]) * (x[i]-y[i]);
    return distance;
}

void WVneighborInit()
{
    vector<vector<double> > distance(populationSize,vector<double>(populationSize,0));
    for(int i=0;i<populationSize;i++){
        for(int j=i;j<populationSize;j++){
            if(i==j) {
                distance[i][j] = numeric_limits<double>::max();
                continue;
            }
            double d=eularDistance(lambda[i],lambda[j],numObjective);
            distance[i][j]=d;
            distance[j][i]=d;
        }
    }

    for(int i=0;i<populationSize;i++){
        for(int k=0;k<T;k++){
            double min = distance[i][0];
            double min_index = 0;
            for(int j=1;j<populationSize;j++){
                if(distance[i][j]<min){
                    min = distance[i][j];
                    min_index = j;
                }
            }
            WVneighbors[i][k] = min_index;
            distance[i][min_index] = numeric_limits<double>::max();
        }
    }
    //cout << "WVneighborInit" << endl;
}

void populationInit()
{
    for(int i=0;i<populationSize;i++){
        for(int j=0;j<dimension;j++){
            population[i][j] = (rand() % 100) / 100.0;
        }
        FV[i] = Fx(population[i]);
    }

    for(int i=0;i<numObjective;i++){
        double min = numeric_limits<double>::max();
        for(int j=0;j<populationSize;j++){
            double fValue = fx(i,population[j],dimension);
            min = min < fValue ? min : fValue;
        }
        z[i] = min;
    }

    //初始化种群在每个目标函数上的值
    for (int j = 0; j<numObjective; j++)
        for (int k = 0; k<populationSize; k++)
            populationfValue[j][k] = fx(j, population[k], dimension);
}

vector<double> make_new_solution_DE(int r1, int r2, int r3)
{
    vector<double> y(dimension);
    for (int k = 0; k<dimension; k++) {
        if (((rand() % 100) / 100.0) <= CR)
            y[k] = population[r1][k] + F*(population[r2][k] - population[r3][k]);
        else
            y[k] = population[r1][k];
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

    //Repair
    for (int k = 0; k<dimension; k++)
        if (y[k]<lowerBound || y[k]>upperBound){
            double randnum = (rand() % 100) / 100.0;
            y[k] = lowerBound + (upperBound-lowerBound)*randnum;
        }

    return y;
}


double subproblemValue(int index, vector<double> x)
{
    double value = 0.0;
    for(int i=0;i<numObjective;i++)
        value += lambda[index][i] * fx(i,x,dimension);
    return value;
}

void updateThePopulation()
{
    for(int i=0;i<populationSize;i++){
        //Step 2.1 Selection of Mating/Update Range
        double randnum = (rand() % 100) / 99.0;
        vector<int> P;
        if(randnum < Delte){
            P.resize(T);
            P = WVneighbors[i];
        }
        else{
            P.resize(populationSize);
            for(int j=0;j<populationSize;j++)
                P[j] = j;
        }

        //Step 2.2 Reproduction
        //随机选三个向量
        int r1 = i;
        vector<bool> selected(P.size(),false);
        selected[r1] = true;
        int p[3];
        for(int k=0;k<3;k++){
            p[k] = rand() % P.size();
            while(selected[p[k]]){
                p[k] = rand() % P.size();
            }
            selected[p[k]] = true;
        }

        r1=i;
        int r2=p[1],r3=p[2];

        //Step 2.2 Reproduction && Step 2.3 Repair:
        //使用DE方法产生新解
        vector<double> y = make_new_solution_DE(r1,r2,r3);

        //Step 2.4 Update of z:
        for(int j=0;j<numObjective;j++){
            double fValue = fx(j,y,dimension);
            z[j] = z[j] < fValue ? z[j] : fValue;
        }

        //Step 2.5 Update of Solutions
        int c=0;
        int leftP = P.size();
        while(true){
            if(c==nr || leftP==0) break;

            int j;
            while(1){
                int index = rand() % P.size();
                j = P[index];
                if(j!=-1){
                    //Remove j from P
                    P[index] = -1;
                    leftP--;
                    break;
                }
            }

            if(subproblemValue(j,y) < subproblemValue(j,population[j])){
                population[j] = y;
                FV[j] = Fx(y);
                c ++;
            }
        }
    }
    //cout << "updateThePopulation" << endl;
}

void MOEA_D()
{
    if(numObjective==2)
        populationSize = 300;
    else if(numObjective == 3)
        populationSize = 595;

    //Step 1 Initialization
    //初始化权值矩阵
    weightVectorGenerator();
    //初始化种群
    populationInit();

    //Step 3 Stopping Criterion
    for(int i=0;i<generationSize;i++){

        //Step 2 Update
        updateThePopulation();

        //更新种群在每个目标函数上的值
        for (int j = 0; j<numObjective; j++)
            for (int k = 0; k<populationSize; k++)
                populationfValue[j][k] = fx(j, population[k], dimension);
    }

    //输出最终种群的优化结果F(x)
    for (int i = 0; i<populationSize; i++)
        cout << FV[i] << " ";
    //输出最终种群在每个目标上的优化结果
    for (int i = 0; i<populationSize; i++) {
        cout << "(";
        for (int k = 0; k<numObjective - 1; k++)
            cout << populationfValue[k][i] << ",";
        cout << populationfValue[numObjective - 1][i] << ")" << endl;
    }

}
}

#endif // MOEA_D_H

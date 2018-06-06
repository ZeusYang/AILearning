#include "MOP_Algorithm.h"
#include <QDebug>

int problemNum = 1;

MOP_Algorithm::MOP_Algorithm(QObject *parent)
    : QObject(parent)
{
    this->InitParameter();
    shouldStop = false;
    isBegin = false;
    problemNum = 1;
}

MOP_Algorithm::~MOP_Algorithm()
{
}

void MOP_Algorithm::InitParameter()
{
    numObjective = 3;
    lowerBound = 0.0;
    upperBound = 1.0;
    dimension = numObjective + 4;
    populationSize = 300;
    generationSize = 500;

    CR = 1.0;
    F = 0.5;
    H = 20; //η
    pm = 1.0 / dimension;
}

void MOP_Algorithm::setGroup(int group)
{
    populationSize = group;
}

void MOP_Algorithm::setGeneration(int gen)
{
    generationSize = gen;
}

void MOP_Algorithm::setObjective(int object)
{
    numObjective = object;
    dimension = numObjective + 4;
}

void MOP_Algorithm::setDimension(int dimension)
{
    this->dimension = dimension;
    pm = 1.0f / dimension;
}

int MOP_Algorithm::getGroup()
{
    return populationSize;
}

int MOP_Algorithm::getGeneration()
{
    return generationSize;
}

int MOP_Algorithm::getObjective()
{
    return numObjective;
}

int MOP_Algorithm::getDimension()
{
    return dimension;
}

//double gx(const vector<double> &x,int numObjective, int dimension)
//{
//    double result = 0.0;
//    for (int i = numObjective-1; i < dimension; i++)
//        result += pow(x[i] - 0.5, 2.0);
//    return result;
//}

////单目标：f（index）指目标index的函数f
//double fx(int index, const vector<double> &x,
//          int numObjective, int dimension)
//{
//    int M = numObjective;
//    double result;
//    result = 1 + gx(x, numObjective, dimension);

//    for (int i = 0; i<M - index - 1; i++) {
//        result *= cos(pow(x[i], PI)*PI / 2);
//    }
//    if (index>0)
//        result *= sin(pow(x[M - index - 1], PI)*PI / 2);

//    return result;
//}

////多目标优化函数 min F=f1+f2+f3+……
//double Fx(const vector<double> &x, int numObjective, int dimension)
//{
//    double result = 0;
//    for (int i = 0; i<numObjective; i++)
//        result += fx(i, x, numObjective, dimension);
//    return result;
//}

double gx(const vector<double> &x,int numObjective, int dimension)
{
    double result = 0.0;
    if(problemNum==1 || problemNum==3){
        for (int i = numObjective-1; i<dimension; i++)
            result += pow(x[i] - 0.5, 2.0) - cos(20*PI*(x[i]-0.5));
        result += dimension-numObjective+1;
        result /= 10;
    }
    else if(problemNum==2 || problemNum==4){
        for (int i = numObjective-1; i<dimension; i++)
            result += pow(x[i] - 0.5, 2.0);
    }
    return result;
}

//单目标：f（index）指目标index的函数f
double fx(int index,const vector<double> &x,
          int numObjective, int dimension)
{
    int M = numObjective;
    double result;
    result = 1 + gx(x, numObjective, dimension);

    if(problemNum==1){
        result *= 0.5;
        for(int i = 0;i<M - index - 1;i++)
            result *= x[i];
        if(index>0)
            result *= (1-x[M-index-1]);
    }
    else if(problemNum==2||problemNum==3){
        for (int i = 0; i<M - index - 1; i++) {
            result *= cos(x[i] * PI / 2.0);
        }
        if (index>0)
            result *= sin(x[M - index - 1] * PI / 2.0);
    }
    else if(problemNum==4){
        for (int i = 0; i<M - index - 1; i++) {
            result *= cos(pow(x[i], PI)*PI / 2);
        }
        if (index>0)
            result *= sin(pow(x[M - index - 1], PI)*PI / 2);
    }

    return result;
}

//多目标优化函数 min F=f1+f2+f3+……
double Fx(const vector<double> &x, int numObjective, int dimension)
{
    double result = 0;
    for (int i = 0; i<numObjective; i++)
        result += fx(i, x, numObjective, dimension);
    return result;
}


#include <ctime>
#include <cmath>
#include <cstdlib>
#include "algorithm.h"
#include "MyFunction.cpp"
#include <QDebug>
#include <iostream>
#include <float.h>

void Algorithm::dataInitialization(int func_num, int dimension)
{
    initialization(func_num, dimension);
}

void Algorithm::resetParameters(std::vector<std::pair<QString, double> > &parm)
{
    for(auto it = parm.begin();it != parm.end();++it){
        this->setParameters(it->first,it->second);
    }
}

void Algorithm::initial()
{
    //初始化
    minY = DBL_MAX;
    maxY = -11000000;
    srand((unsigned)time(NULL));
    int population = static_cast<int>(getParameters(tr("population")));//种群大小
    int dimension = static_cast<int>(getParameters(tr("dimension")));//维度
    int generation = static_cast<int>(getParameters(tr("generation")));//迭代次数
    double lowbounding = getParameters(tr("lowbounding"));
    double upbounding = getParameters(tr("upbounding"));
    group.clear();
    group.resize(generation,std::vector<std::vector<double> >(population,
                            std::vector<double>(dimension,0.0)));
    for (int i = 0; i < population; i++) {
        for (int j = 0; j < dimension; j++) {
            group[0][i][j] = lowbounding +
                    (double)(rand() / (double)RAND_MAX) * (upbounding - lowbounding);
        }
    }
    currentValue.clear();
    currentValue.resize(population,0.0);
}

double Algorithm::getResult(std::vector<double> ans)
{
    int dimension = static_cast<int>(getParameters(tr("dimension")));
    int func_num = static_cast<int>(getParameters(tr("function")));//函数编号
    return functions(ans,func_num,dimension);
}

void Algorithm::calcCurrentValue(const std::vector<std::vector<double> > &target)
{
    minY = DBL_MAX;
    maxY = -11000000;
    avgValue = 0;
    int dimension = static_cast<int>(getParameters(tr("dimension")));
    int func_num = static_cast<int>(getParameters(tr("function")));//函数编号
    for(uint x = 0;x < target.size();++x){
        currentValue[x] = functions(target[x],func_num,dimension);
        avgValue += currentValue[x];
        minY = std::min(minY,currentValue[x]);
        maxY = std::max(maxY,currentValue[x]);
    }
    avgValue /= target.size();
}

//以下为粒子群算法
void PSOAlgorithm::initial()
{
    Algorithm::initial();
    int population = static_cast<int>(getParameters(tr("population")));//种群大小
    int dimension = static_cast<int>(getParameters(tr("dimension")));//维度
    gBest.clear();
    pBest.clear();
    velocity.clear();
    gBest.resize(dimension, 0.0);
    pBest.resize(population,std::vector<double>(dimension, 0.0));
    velocity.resize(population,std::vector<double>(dimension,0.0));
    bestValue.first = 0;
    bestValue.second = DBL_MAX;
}

void PSOAlgorithm::process()
{
    curAndgloBest(0);//计算初始代最优解
    int generation = static_cast<int>(getParameters(tr("generation")));//迭代次数
    for (auto current = 1; current < generation; ++current) {
        update(current);
        curAndgloBest(current);
        calcCurrentValue(pBest);
        if(generation <= 100 || (generation > 100 && generation % 2 == 0))
            emit frameUpdate(avgValue,currentValue,minY,maxY,current,generation,bestValue);
    }
    emit processFinished(bestValue.second);
}

void PSOAlgorithm::update(int curGeneration)
{//更新速度和位置
    int dimension = static_cast<int>(getParameters(tr("dimension")));
    int population = static_cast<int>(getParameters(tr("population")));
    double w = getParameters(tr("w"));//惯性权重
    double c1 = getParameters(tr("c1"));//加速系数
    double c2 = getParameters(tr("c2"));//加速系数
    double upbounding = getParameters(tr("upbounding"));//上界
    double lowbounding = getParameters(tr("lowbounding"));//下界

    for(auto i = 0;i < population;++i){
        for(auto j = 0;j < dimension;++j){
            double pre = velocity[i][j];
            //更新速度
            velocity[i][j] = w*pre +
                    c1*(double)(rand()/(double)RAND_MAX)*
                    (pBest[i][j] - group[curGeneration - 1][i][j])
                    +
                    c2*(double)(rand()/(double)RAND_MAX)*
                    (gBest[j] - group[curGeneration - 1][i][j]);
            if(velocity[i][j] > 200)velocity[i][j] = 200;
            //位置更新
            group[curGeneration][i][j] = group[curGeneration-1][i][j] + velocity[i][j];
            //边界处理
            if(group[curGeneration][i][j] > upbounding)
                group[curGeneration][i][j] = upbounding;
            if(group[curGeneration][i][j] < lowbounding)
                group[curGeneration][i][j] = lowbounding;
        }
    }
}

void PSOAlgorithm::curAndgloBest(int curGeneration)
{//计算当前最优解和全局最优解
    int population = static_cast<int>(getParameters(tr("population")));
    int dimension = static_cast<int>(getParameters(tr("dimension")));
    int func_num = static_cast<int>(getParameters(tr("function")));//函数编号
    for (auto i = 0; i < population; ++i) {
            double value = functions(group[curGeneration][i], func_num, dimension);
            if (value < functions(pBest[i], func_num, dimension))
                pBest[i] = group[curGeneration][i];
            if (functions(pBest[i], func_num, dimension) < functions(gBest, func_num, dimension)){
                gBest = pBest[i];
                bestValue.first = i;
                bestValue.second = functions(pBest[i], func_num, dimension);
            }
    }
}

//以下为差分进化算法
void DEAlgorithm::initial()
{
    Algorithm::initial();
    int dimension = static_cast<int>(getParameters(tr("dimension")));//维度
    solution.clear();
    solution.resize(dimension,0.0);
}

void DEAlgorithm::process()
{
    int population = static_cast<int>(getParameters(tr("population")));//种群大小
    int dimension = static_cast<int>(getParameters(tr("dimension")));//维度
    int generation = static_cast<int>(getParameters(tr("generation")));//迭代次数
    double lowbounding = getParameters(tr("lowbounding"));
    double upbounding = getParameters(tr("upbounding"));
    double DE_F = getParameters(tr("F"));//缩放因子
    double DE_CR = getParameters(tr("CR"));//交叉概率
    int func_num = static_cast<int>(getParameters(tr("function")));//函数编号
    double bestSolution = 100000000;//目前全局最优解
    //开始迭代
    for(auto t=1;t<generation;t++){
        //变异
        for(int i=0;i<population;i++){
            //随机选三个向量
            std::vector<bool> selected(population,false);
            selected[i] = true;
            int pick[3];
            for(auto k=0;k<3;k++){
                pick[k] = rand() % population;
                while(selected[pick[k]])pick[k] = rand() % population;
                selected[pick[k]] = true;
            }
            for(auto j=0;j<dimension;j++){
                //变异操作公式
                group[t][i][j] = group[t-1][pick[0]][j] +
                        DE_F * (group[t-1][pick[1]][j] - group[t-1][pick[2]][j]);
                //边界处理
                if(group[t][i][j]<lowbounding) group[t][i][j] = lowbounding;
                else if(group[t][i][j]>upbounding) group[t][i][j] = upbounding;
            }
        }
        //交叉
        for(auto i=0;i<population;i++){
            for(auto j=0;j<dimension;j++){
                if(((rand() % 100) / 100.0) <= DE_CR || j == (rand() % dimension))
                    group[t][i][j] = group[t][i][j];
                else
                    group[t][i][j] = group[t-1][i][j];
            }
        }
        //选择替换，贪心策略
        for(auto i=0;i<population;i++){
            if(functions(group[t][i],func_num,dimension) <=
                    functions(group[t-1][i],func_num,dimension)){
                group[t][i] = group[t][i];
                bestSolution =
                        bestSolution < functions(group[t][i],func_num,dimension)
                        ? bestSolution : functions(group[t][i],func_num,dimension);
                if(bestSolution < functions(group[t][i],func_num,dimension)){
                    bestValue.first = i;
                    bestValue.second = bestSolution;
                    solution = group[t][i];
                }
            }
            else{
                group[t][i] = group[t-1][i];
            }
        }
        //计算当前种群的全部值
        calcCurrentValue(group[t]);
        if(generation > 300 && generation % 2 == 0){
            emit frameUpdate(avgValue,currentValue,minY,maxY,t,generation,bestValue);
        }
        else{
            emit frameUpdate(avgValue,currentValue,minY,maxY,t,generation,bestValue);
        }
    }
    emit processFinished(bestValue.second);
}

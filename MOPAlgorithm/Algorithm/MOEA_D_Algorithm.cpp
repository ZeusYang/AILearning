#include "MOEA_D_Algorithm.h"
#include <QVector3D>
#include <QDebug>

MOEA_D_Algorithm::MOEA_D_Algorithm()
    :MOP_Algorithm(nullptr)
{
    this->setObjective(3);
    this->setGroup(595);
}

MOEA_D_Algorithm::~MOEA_D_Algorithm() {}

void MOEA_D_Algorithm::AlgorithmProcess()
{
    isBegin = true;
    Initial();
    srand(time(nullptr));
    vector<QVector3D> paratoFace;
    //Step 1 Initialization
    //初始化权值矩阵
    weightVectorGenerator();
    //Step 2 初始化种群
    populationInit();
    //Step 3 Stopping Criterion
    for(int i = 0;i < generationSize;i++){
        //Step 4 Update
        updateThePopulation();
        //更新种群在每个目标函数上的值
        for (int j = 0; j<numObjective; j++){
            for (int k = 0; k<populationSize; k++){
                populationfValue[j][k] = fx(j, population[k],
                                            numObjective, dimension);
            }
        }

        //可视化
        paratoFace.clear();
        paratoFace.reserve(populationSize);
        for(int k = 0;k < populationSize;++k){
            QVector3D data;
            if(numObjective == 2){
                data.setX(populationfValue[0][k]);
                data.setY(populationfValue[1][k]);
                data.setZ(0);
            }
            else if(numObjective == 3){
                data.setX(populationfValue[0][k]);
                data.setY(populationfValue[1][k]);
                data.setZ(populationfValue[2][k]);
            }
            paratoFace.push_back(data);
        }
        emit sendData(paratoFace);
        // progress
        emit sendProgress((float)(i+1.0f)/generationSize);
        if(shouldStop){
            shouldStop = false;
            isBegin = false;
            return;
        }
    }
    isBegin = false;
}

void MOEA_D_Algorithm::Initial()
{
    //δ:the probability that parent solutions are selected from the neighborhood
    Delte = 0.9;
    //the maximal number of solutions replaced by each child solution.
    nr = 2;
    //T closest weight vectors to each weight vector
    T = 20;
    population.resize(populationSize,vector<double>(dimension,0.0));
    FV.resize(populationSize,0.0);  //FV[i] = F(x[i])
    //z[i] the best value found so far for objective fi
    z.resize(numObjective,0.0);
    lambda.resize(populationSize,vector<double>(numObjective,0.0)); //权值矩阵
    WVneighbors.resize(populationSize,vector<int>(T,0)); //权值向量的邻居下标
    populationfValue.resize(numObjective, vector<double>(2 * populationSize));
}

void MOEA_D_Algorithm::populationInit()
{
    //随机初始化种群
    //FV[i] = F(x[i])
    for(int i = 0;i < populationSize;i++){
        for(int j = 0;j < dimension;j++){
            population[i][j] = (rand() % 100) / 99.0;
        }
        FV[i] = Fx(population[i], numObjective, dimension);
    }

    //z[i] the best value found so far for objective fi
    for(int i = 0;i < numObjective;i++){
        double min = numeric_limits<double>::max();
        for(int j = 0;j < populationSize;j++){
            double fValue = fx(i,population[j], numObjective, dimension);
            min = min <= fValue ? min : fValue;
        }
        z[i] = min;
    }

    //初始化种群在每个目标函数上的值
    for (int j = 0; j < numObjective; j++)
        for (int k = 0; k < populationSize; k++)
            populationfValue[j][k] = fx(j, population[k],
                                        numObjective, dimension);
}

void MOEA_D_Algorithm::updateThePopulation()
{
    for(int i = 0;i < populationSize;i++){
        //Step 2.1 Selection of Mating/Update Range
        double randnum = (rand() % 100) / 99.0;
        vector<int> P;
        //the probability that parent solutions are selected from the neighborhood
        if(randnum < Delte){
            P.resize(T);
            P = WVneighbors[i];
        }
        else{
            P.resize(populationSize);
            for(int j = 0;j < populationSize;j++)
                P[j] = j;
        }

        //Step 2.2 Reproduction
        //随机选三个向量
        int p[3];
        p[0] = i;
        p[1] = rand() % P.size();
        while(p[1] == p[0])p[1] = rand() % P.size();
        p[2] = rand() % P.size();
        while(p[2] == p[0] || p[2] == p[1])p[2] = rand() % P.size();

        int r1 = p[0], r2 = P[p[1]],r3 = P[p[2]];

        //Step 2.2 Reproduction && Step 2.3 Repair:
        //使用DE方法产生新解
        vector<double> y = make_new_solution_DE(r1,r2,r3);

        //Step 2.4 Update of z:
        //更新每个目标的最优解
        for(int j = 0;j < numObjective;j++){
            double fValue = fx(j,y,numObjective,dimension);
            z[j] = z[j] < fValue ? z[j] : fValue;
        }

        //Step 2.5 Update of Solutions
        int c = 0;
        int leftP = P.size();
        while(true){
            if(c == nr || leftP == 0) break;

            int j;
            while(1){
                int index = rand() % P.size();
                j = P[index];
                if(j != -1){
                    //Remove j from P
                    P[index] = -1;
                    leftP--;
                    break;
                }
            }

            //贪心策略
            if(subproblemValue(j,y) < subproblemValue(j,population[j])){
                population[j] = y;
                FV[j] = Fx(y,numObjective,dimension);
                c ++;
            }
        }
    }
}

void MOEA_D_Algorithm::weightVectorGenerator()
{
    //vector<QVector3D> data;
    for(int i = 0;i < populationSize;i++){
        double sum = 0;
        if(numObjective == 2){
            int index = rand()%(sizeof(NBI_2)/sizeof(double));
            lambda[i][0] = NBI_2[index];
            lambda[i][1] = 1.0f-NBI_2[index];
        }
        else if(numObjective == 3){
            int l1,l2,l3;
            l1 = rand()%3;
            l2 = rand()%3;
            while(l1 == l2) l2 = rand()%3;
            l3 = 3 - l1 - l2;
            int index1 = rand()%(sizeof(NBI_3)/sizeof(double));
            lambda[i][l1] = NBI_3[index1];
            int index2 = rand()%(sizeof(NBI_3)/sizeof(double));
            while(NBI_3[index2]+NBI_3[index1]>1.0f)
                index2 = rand()%(sizeof(NBI_3)/sizeof(double));
            lambda[i][l2] = NBI_3[index2];
            lambda[i][l3] = 1.0f-NBI_3[index1]-NBI_3[index2];
        }
        //        QVector3D tmp;
        //        tmp.setX(lambda[i][0]);
        //        tmp.setY(lambda[i][1]);
        //        tmp.setZ(lambda[i][2]);
        //        data.push_back(tmp);
    }
    //emit sendData(data);
    WVneighborInit();
}

void MOEA_D_Algorithm::WVneighborInit()
{
    //计算距离
    vector<vector<double> > distance(populationSize,
                                     vector<double>(populationSize,0));
    for(int i = 0;i < populationSize;i++){
        for(int j = i;j < populationSize;j++){
            if(i == j) {
                distance[i][j] = numeric_limits<double>::max();
                continue;
            }
            double d = eularDistance(lambda[i],lambda[j],numObjective);
            distance[i][j] = d;
            distance[j][i] = d;
        }
    }

    // 计算前T个最邻近的权值向量
    for(int i = 0;i < populationSize;i++){
        for(int k = 0;k < T;k++){
            double min = distance[i][0];
            double min_index = 0;
            for(int j = 1;j < populationSize;j++){
                if(distance[i][j] < min){
                    min = distance[i][j];
                    min_index = j;
                }
            }
            // 存储的是下标
            WVneighbors[i][k] = min_index;
            distance[i][min_index] = numeric_limits<double>::max();
        }
    }
}

double MOEA_D_Algorithm::subproblemValue(int index,const vector<double> &x)
{
    //计算子问题的值
    double value = numeric_limits<double>::min();
    for(int i = 0;i < numObjective;i++){
        double tmp = lambda[index][i] * abs(fx(i,x,numObjective,dimension)-z[i]);
        if(tmp > value)value = tmp;
    }
    return value;
}

vector<double> MOEA_D_Algorithm::make_new_solution_DE(int r1, int r2, int r3)
{
    //遗传算法的操作
    vector<double> y(dimension);
    for (int k = 0; k<dimension; k++) {
        if (((rand() % 100) / 100.0) <= CR)
            y[k] = population[r1][k] +
                    F*(population[r2][k] - population[r3][k]);
        else
            y[k] = population[r1][k];
    }

    for (int k = 0; k < dimension; k++) {
        if (((rand() % 100) / 100.0) <= pm) {
            double r = (rand() % 100) / 100.0;
            double dk;
            if (r < 0.5)
                dk = pow(2 * r, 1.0 / (1 + H)) - 1;
            else
                dk = 1 - pow((2 - 2 * r), 1.0 / (1 + H));

            y[k] = y[k] + dk*(upperBound - lowerBound);
        }
    }

    //Repair
    for (int k = 0; k < dimension; k++){
        if (y[k] < lowerBound || y[k] > upperBound){
            double randnum = (rand() % 100) / 100.0;
            y[k] = lowerBound + (upperBound-lowerBound)*randnum;
        }
    }

    return y;
}

double MOEA_D_Algorithm::eularDistance(const vector<double> &x,
                                       const vector<double> &y,
                                       int size)
{
    //欧式距离
    double distance=0;
    for(int i = 0;i < size;i++)
        distance += (x[i]-y[i]) * (x[i]-y[i]);
    return distance;
}

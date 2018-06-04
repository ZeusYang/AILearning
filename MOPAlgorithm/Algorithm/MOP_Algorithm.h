#ifndef MOP_ALGORITHM_H
#define MOP_ALGORITHM_H

#include <QObject>
#include <vector>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <ctime>
#include <functional>
#define INFINIT 0xffffffff

using namespace std;
using namespace std::placeholders;
/*
 * multi-objects problem
 */
class MOP_Algorithm : public QObject
{
    Q_OBJECT
public:
    bool isBegin;
    bool shouldStop;
    explicit MOP_Algorithm(QObject *parent = nullptr);
    virtual ~MOP_Algorithm();

    void InitParameter();

    virtual void AlgorithmProcess() = 0;

    void setGroup(int group);
    void setGeneration(int gen);
    void setObjective(int object);
    void setDimension(int dimension);

    int getGroup();
    int getGeneration();
    int getObjective();
    int getDimension();
signals:
    void sendProgress(double progress);
    void sendData(const vector<QVector3D> &data);

protected:
#define PI 3.1415926535898
    double lowerBound;
    double upperBound;
    int dimension;
    int numObjective;
    int populationSize;
    int generationSize;

    // DE paramter
    double CR;
    double F;
    double H; //η
    double pm;
};

// functions
double gx(const vector<double> &x, int numObjective, int dimension);
double fx(int index,const vector<double> &x, int numObjective, int dimension);
double Fx(const vector<double> &x, int numObjective, int dimension);

#endif // MOP_ALGORITHM_H

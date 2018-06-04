#ifndef NSGA_II_ALGORITHM_H
#define NSGA_II_ALGORITHM_H
#include "MOP_Algorithm.h"
#include <QVector3D>

class NSGA_II_Algorithm : public MOP_Algorithm
{
    Q_OBJECT
public:
    NSGA_II_Algorithm();
    virtual ~NSGA_II_Algorithm();

    void Initial();

    virtual void AlgorithmProcess();
private:
    vector<vector<double> > populationfValue;
    vector<double> fMax;
    vector<double> fMin;

    bool dominatedCompare(int p, int q, int dimension);

    //以下标的方式返回种群P的前沿面
    vector<vector<int> > fast_non_dominated_sort(vector<vector<double> >& P,
                                                 int size, int dimension);

    // 拥挤距离排序
    //需要计算拥挤距离的个体按照目标m依照fm的大小进行排序 需要用到的比较器
    vector<double> crowding_distance_assignment(vector<int>& I, int size);

    void make_new_generation_DE(vector<vector<double>>& parent,
                                int size, vector<vector<double>>& offspring);

    //进行需要计算拥挤距离的个体按照目标m依照fm的大小进行排序的辅助结构体
    struct assist {
        int index;
        int objective;
        assist(int i, int m) {
            index = i;
            objective = m;
        }
    };
    //用于拥挤距离辅助排序的结构体
    struct Idistance {
        int index;
        double distance;

        Idistance(int i, double d) {
            index = i;
            distance = d;
        }
    };
};

inline bool NSGA_II_Algorithm::dominatedCompare(int p, int q, int dimension)
{
    Q_UNUSED(dimension);
    bool LE = true; //less or equal
    bool L = false; //less
    for (int i = 0; i<numObjective; i++) {
        if (populationfValue[i][p] > populationfValue[i][q]) LE = false;
        if (populationfValue[i][p] < populationfValue[i][q]) L = true;
    }
    return LE&&L;
}

#endif // NSGA_II_ALGORITHM_H

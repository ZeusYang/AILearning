#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <map>
#include <QString>
#include <QObject>
#include <vector>

class Algorithm : public QObject
{
    Q_OBJECT
public:
    double result;//存储结果

    static void dataInitialization(int func_num, int dimension);

    Algorithm():minY(0.0),maxY(10000000000.0){}

    void setParameters(const QString &target, double value){
        parameters[target] = value;
    }

    double getParameters(const QString &target){
        return parameters[target];
    }

    void resetParameters(std::vector<std::pair<QString,double> > &parm);//设置参数

    virtual void initial(){
        return;
    }

    virtual void process(){
        return;
    }

    double getResult(std::vector<double> ans);

    std::map<QString,double>& getParameterList(){
        return parameters;
    }
signals:
    void processFinished(double result);
    void frameUpdate(double midret,const std::vector<double>& target,
                     const double &ymin,const double &ymax,
                     const int &curGen,const int &totalGen,
                     const std::pair<int,double> &bestValue);//运行过程中的动态更新

protected:
    std::vector<std::vector<std::vector<double> > > group;//群体
    std::vector<double> currentValue;
    std::pair<int,double> bestValue;
    double minY,maxY;

    void calcCurrentValue(const std::vector<std::vector<double> > &target);

private:
    std::map<QString, double> parameters;//参数列表
};

class PSOAlgorithm : public Algorithm{//粒子群算法
    Q_OBJECT
public:
    std::vector<double> gBest; //全局最优解

    PSOAlgorithm(){}

    virtual void initial();

    virtual void process();

    void update(int curGeneration);//更新速度和位置

    void curAndgloBest(int curGeneration);//计算全局最优与当前最优

private:
    std::vector<std::vector<double> >velocity;//速度
    std::vector<std::vector<double> >pBest;//当前每个的最优解
};

class DEAlgorithm : public Algorithm{//差分进化算法
    Q_OBJECT
public:
    std::vector<double> solution;

    DEAlgorithm(){}

    virtual void initial();

    virtual void process();
};

#endif // ALGORITHM_H

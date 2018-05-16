#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>

namespace Ui {
class MainWindow;
}

class PSOParameters;
class PSOAlgorithm;
class DEAlgorithm;
//class QScatterSeries;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected slots:
    void setParameters(QString target, double value, bool type);
    void beginProcess(bool type);//开始运行
    void setResult(double result);//设置结果数值
    void frameUpdate(double midret,const std::vector<double>& target,
                     const double &ymin,const double &ymax,
                     const int &curGen,const int &totalGen,
                     const std::pair<int,double> &bestValue);//运行过程中的动态设置
private:
    bool begin;
    Ui::MainWindow *ui;
    PSOParameters *setting;
    PSOAlgorithm* pso_algo;
    DEAlgorithm* de_algo;
    QtCharts::QScatterSeries *series;
    QtCharts::QScatterSeries *bestSol;
    QtCharts::QChartView *chartView;

    //参数列表
    std::vector<std::pair<QString,double> > psoParm;
    std::vector<std::pair<QString,double> > deParm;
};

#endif // MAINWINDOW_H

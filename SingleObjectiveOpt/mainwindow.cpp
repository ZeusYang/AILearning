#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "psoparameters.h"
#include "algorithm.h"
#include <QtCharts/QChart>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QDebug>
using namespace QtCharts;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),begin(false)
{
    ui->setupUi(this);
    QWidget *centeral = new QWidget(this);
    this->setCentralWidget(centeral);

    setting = new PSOParameters(this);
    connect(setting,&PSOParameters::changeParameter,this,&MainWindow::setParameters);
    connect(setting,&PSOParameters::beginToProcess,this,&MainWindow::beginProcess);

    // 构建图表
    QChart *chart = new QChart();
    chart->legend()->hide();  // 隐藏图例
    // 构建 series，作为图表的数据源
    series = new QtCharts::QScatterSeries(chart);
    series->setMarkerSize(10.0);
    bestSol = new QScatterSeries(chart);
    bestSol->setMarkerSize(25.0);
    chart->addSeries(series);  // 将 series 添加至图表中
    chart->addSeries(new QScatterSeries(chart));
    chart->addSeries(bestSol); //将bestSol 添加至图表中
    chart->createDefaultAxes();  // 基于已添加到图表的 series 来创轴
    chart->setTitle(tr("种群个体适应值"));  // 设置图表的标题
    chart->axisX()->setTitleText(tr("种群个体编号"));
    chart->axisY()->setTitleText(tr("函数值"));

    // 构建 QChartView，并设置抗锯齿、标题、大小
    chartView = new QChartView(this);
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setWindowTitle(tr("种群个体适应值"));
    QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(2);
    chartView->chart()->setTheme(theme);

    //布局
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(chartView);
    layout->addWidget(setting);
    layout->setStretchFactor(chartView,2);
    layout->setStretchFactor(setting,1);
    centeral->setLayout(layout);

    //算法处理部分
    pso_algo = new PSOAlgorithm();
    de_algo = new DEAlgorithm();
    connect(pso_algo,&PSOAlgorithm::processFinished,this,&MainWindow::setResult);
    connect(de_algo,&DEAlgorithm::processFinished,this,&MainWindow::setResult);
    connect(pso_algo,&PSOAlgorithm::frameUpdate,this,&MainWindow::frameUpdate);
    connect(de_algo,&DEAlgorithm::frameUpdate,this,&MainWindow::frameUpdate);
    psoParm = {
        std::pair<QString,double>("population",50.0),
        std::pair<QString,double>("dimension",2.0),
        std::pair<QString,double>("function",1.0),
        std::pair<QString,double>("generation",200),
        std::pair<QString,double>("w",0.5),
        std::pair<QString,double>("c1",2.0),
        std::pair<QString,double>("c2",2.0),
        std::pair<QString,double>("upbounding",100.0),
        std::pair<QString,double>("lowbounding",-100.0)
    };
    deParm = {
        std::pair<QString,double>("population",30),
        std::pair<QString,double>("dimension",2.0),
        std::pair<QString,double>("function",1.0),
        std::pair<QString,double>("generation",150),
        std::pair<QString,double>("F",0.5),
        std::pair<QString,double>("CR",0.3),
        std::pair<QString,double>("upbounding",100.0),
        std::pair<QString,double>("lowbounding",-100.0)
    };
    pso_algo->resetParameters(psoParm);
    de_algo->resetParameters(deParm);
    setting->showParameters(pso_algo->getParameterList(),de_algo->getParameterList());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pso_algo;
    delete de_algo;
}

void MainWindow::setParameters(QString target, double value, bool type)
{
    if(!type){
        for(auto it = psoParm.begin();it != psoParm.end();++it){
            if(it->first == target){
                it->second = value;
                pso_algo->setParameters(target,value);
                break;
            }
        }
    }
    else{
        for(auto it = deParm.begin();it != deParm.end();++it){
            if(it->first == target){
                it->second = value;
                de_algo->setParameters(target,value);
                break;
            }
        }
    }
}

void MainWindow::beginProcess(bool type)
{
    if(begin){
        QMessageBox::warning(this,tr("警告"),
                             tr("当前算法任务尚未完成!"));
        return;
    }
    begin = true;
    if(!type){//粒子群
        Algorithm::dataInitialization(static_cast<int>(pso_algo->getParameters("function")),
                                      static_cast<int>(pso_algo->getParameters("dimension")));
        pso_algo->initial();
        pso_algo->process();
    }
    else{
        Algorithm::dataInitialization(static_cast<int>(de_algo->getParameters("function")),
                                      static_cast<int>(de_algo->getParameters("dimension")));
        de_algo->initial();
        de_algo->process();
    }
}

void MainWindow::setResult(double result)
{
    setting->setResult(result);
    begin = false;
}

void MainWindow::frameUpdate(double midret,const std::vector<double> &target,
                             const double &ymin,const double &ymax,
                             const int &curGen,const int &totalGen,
                             const std::pair<int,double> &bestValue)
{
    //设置显示结果
    setting->setResult(midret);
    //设置显示图表
    chartView->chart()->axisX()->setRange(-1,target.size()+1);
    chartView->chart()->axisY()->setRange(ymin-10,ymax+10);
    series->clear();
    for(uint x = 0;x < target.size();++x){
        series->append(x,target[x]);
    }
    chartView->repaint();
    //设置显示最优解
    bestSol->clear();
    bestSol->append(bestValue.first,bestValue.second);
    //设置显示进度
    double ratio = static_cast<double>(curGen)/totalGen;
    setting->setProgress(ratio);
}

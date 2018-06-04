#include "Display.h"
#include "ui_Display.h"
#include "Setting.h"
#include <QHBoxLayout>
#include <QFont>
#include <QDebug>

Display::Display(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);

    // visualization widget
    InitGraph();
    QWidget *container = QWidget::createWindowContainer(m_graph);

    setting = new Setting(this);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(container);
    layout->addWidget(setting);
    layout->setStretch(0,2);
    layout->setStretch(1,1);
    this->setLayout(layout);

    // algorithm
    algorithm_nsga = new NSGA_II_Algorithm();
    algorithm_moea = new MOEA_D_Algorithm();
    setting->setMoea_D(algorithm_moea);
    setting->setNsga_II(algorithm_nsga);

    connect(algorithm_nsga,&NSGA_II_Algorithm::sendData,
            this,&Display::setData);
    connect(algorithm_moea,&NSGA_II_Algorithm::sendData,
            this,&Display::setData);
    connect(setting,&Setting::begin,this,&Display::beginProcess);
    connect(algorithm_nsga,&NSGA_II_Algorithm::sendProgress,
            setting,&Setting::setProgress);
    connect(algorithm_moea,&NSGA_II_Algorithm::sendProgress,
            setting,&Setting::setProgress);
}

Display::~Display()
{
    delete ui;
    if(m_graph)delete m_graph;
    if(algorithm_nsga)delete algorithm_nsga;
    if(algorithm_moea)delete algorithm_moea;
}

void Display::setData(const vector<QVector3D> &data)
{
    QScatterDataArray *dataArray = new QScatterDataArray;
    dataArray->resize(data.size());
    QScatterDataItem *ptrToDataArray = &dataArray->first();
    for(auto it = data.begin();it != data.end();++it)
    {
        ptrToDataArray->setPosition(*it);
        ++ptrToDataArray;
    }
    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray);
    //防止未响应
    qApp->processEvents();
}

void Display::beginProcess(int type)
{
    if(type == 0){
        algorithm_nsga->AlgorithmProcess();
    }
    else if(type == 1)
    {
        algorithm_moea->AlgorithmProcess();
    }
}

void Display::InitGraph()
{
    // 3d graph
    m_graph = new Q3DScatter();
    m_graph->activeTheme()->setType(Q3DTheme::ThemeRetro);
    m_graph->setTitle("Pareto Front");
    QFont font = m_graph->activeTheme()->font();
    font.setFamily("幼圆");
    font.setPointSize(50.0f);
    m_graph->activeTheme()->setFont(font);
    m_graph->activeTheme()->setLabelBackgroundEnabled(false);
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);

    QScatterDataProxy *proxy = new QScatterDataProxy;
    m_series = new QScatter3DSeries(proxy);
    m_series->setItemLabelFormat(QStringLiteral("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel"));
    m_series->setMeshSmooth(true);
    m_graph->addSeries(m_series);

    m_graph->axisX()->setTitle("X");
    m_graph->axisY()->setTitle("Y");
    m_graph->axisZ()->setTitle("Z");
    m_graph->axisX()->setRange(0,1.0);
    m_graph->axisY()->setRange(0,1.0);
    m_graph->axisZ()->setRange(0,1.0);
    m_graph->seriesList().at(0)->setMesh(QAbstract3DSeries::MeshPoint);
}

#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QtDataVisualization/QAbstract3DSeries>
#include <QtDataVisualization/Q3DScatter>
#include <QtDataVisualization/QScatter3DSeries>
#include "Algorithm/NSGA_II_Algorithm.h"
#include "Algorithm/MOEA_D_Algorithm.h"

using namespace QtDataVisualization;

namespace Ui {
class Display;
}
class Setting;
class Display : public QWidget
{
    Q_OBJECT

public:
    explicit Display(QWidget *parent = 0);
    ~Display();

private slots:
    void setData(const vector<QVector3D> &data);
    void beginProcess(int type);
private:
    Ui::Display *ui;
    Setting *setting;
    Q3DScatter *m_graph;
    QScatter3DSeries *m_series;
    NSGA_II_Algorithm *algorithm_nsga;
    MOEA_D_Algorithm  *algorithm_moea;

    void InitGraph();
};

#endif // DISPLAY_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include "writeboard.h"
#include "common.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void InitNeuron();
    void TrainProcess();
    void TestErrorRate();
    void Test();
    void ErrorTest();

    void Recognize();
    void Clear();

    void HandTrain();
    void CorrectProcess();

private:
    Ui::MainWindow *ui;
    WriteBoard *panel;
    QLabel *operation;
    QPushButton *clearb;
    QPushButton *getit;
    QPushButton *train;
    QLabel *ret;
    QLineEdit *correction;
    QPushButton *sure;

private:
    //algorithm part
    dataInput src;
    dataInput testData;
    bpNeuronNet* bpnn;

    int imageSize;
    int numImages;
    int epochMax;
    double expectErr;
    bool mode;
};

#endif // MAINWINDOW_H

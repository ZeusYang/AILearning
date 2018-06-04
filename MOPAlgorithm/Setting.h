#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include "Algorithm/MOP_Algorithm.h"

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT
public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();
    void setNsga_II(MOP_Algorithm *nsga);
    void setMoea_D(MOP_Algorithm *moea);
public slots:
    void setProgress(double progress);
signals:
    void begin(int type);
private slots:
    void on_pushButton_clicked();

    void on_algorithmComboBox_currentTextChanged(const QString &arg1);

    void on_groupLineEdit_editingFinished();

    void on_objectComboBox_currentTextChanged(const QString &arg1);

    void on_dimensionComboBox_currentTextChanged(const QString &arg1);

    void on_generationLineEdit_editingFinished();

    void on_pushButton_2_clicked();

private:
    Ui::Setting *ui;
    MOP_Algorithm *algorithm_nsga;
    MOP_Algorithm *algorithm_moea;

    void setParamter(MOP_Algorithm *algorithm);
};

#endif // SETTING_H

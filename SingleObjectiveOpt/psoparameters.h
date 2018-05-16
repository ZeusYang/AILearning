#ifndef PSOPARAMETERS_H
#define PSOPARAMETERS_H

#include <QWidget>
#include <map>

namespace Ui {
class PSOParameters;
}

class PSOParameters : public QWidget
{
    Q_OBJECT

public:
    explicit PSOParameters(QWidget *parent = 0);
    ~PSOParameters();
    void setResult(double result);
    void setProgress(const double &ratio);
    void showParameters( std::map<QString,double> &pso,
                         std::map<QString,double> &de);
signals:
    void changeParameter(QString target, double value, bool type);
    void beginToProcess(bool type);

private slots:
    void on_LineEditGroup_textChanged(const QString &arg1);

    void on_LineEditGroup_textEdited(const QString &arg1);

    void on_LineEditGroup_editingFinished();

    void on_LineEditGeneration_editingFinished();

    void on_LineEditSpeed1_editingFinished();

    void on_LineEditSpeed2_editingFinished();

    void on_LineEditUp_editingFinished();

    void on_LineEditDown_cursorPositionChanged(int arg1, int arg2);

    void on_LineEditDown_editingFinished();

    void on_LineEditGroup_D_editingFinished();

    void on_LineEditGeneration_D_editingFinished();

    void on_LineEditUp_D_editingFinished();

    void on_LineEditDown_D_editingFinished();

    void on_horizontalSliderWeight_valueChanged(int value);

    void on_ComboBoxDimension_currentTextChanged(const QString &arg1);

    void on_horizontalSliderFactor_D_valueChanged(int value);

    void on_horizontalSliderCR_D_valueChanged(int value);

    void on_ComboBoxDimension_D_currentTextChanged(const QString &arg1);

    void on_pushButtonProcess_clicked();

    void on_comboBoxFunction_currentIndexChanged(int index);

    void on_LineEditGeneration_returnPressed();

private:
    Ui::PSOParameters *ui;
};

#endif // PSOPARAMETERS_H

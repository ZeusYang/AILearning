#include "psoparameters.h"
#include "ui_psoparameters.h"
#include <QDebug>

PSOParameters::PSOParameters(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PSOParameters)
{
    ui->setupUi(this);
    //设置输入限制
    ui->LineEditGroup->setValidator(new QIntValidator(10, 300));
    ui->LineEditGeneration->setValidator(new QIntValidator());
    ui->LineEditSpeed1->setValidator(new QDoubleValidator(0.0,10.0,10));
    ui->LineEditSpeed2->setValidator(new QDoubleValidator(0.0, 10.0,10));
    ui->LineEditUp->setValidator(new QDoubleValidator());
    ui->LineEditDown->setValidator(new QDoubleValidator());

    ui->LineEditGroup_D->setValidator(new QIntValidator());
    ui->LineEditGeneration_D->setValidator(new QIntValidator());
    ui->LineEditUp_D->setValidator(new QDoubleValidator());
    ui->LineEditDown_D->setValidator(new QDoubleValidator());

    ui->lineEditResult->setReadOnly(true);
    ui->textEdit->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);
}

PSOParameters::~PSOParameters()
{
    delete ui;
}

void PSOParameters::setResult(double result)
{
    ui->lineEditResult->setText(QString::number(result,10,3));
    ui->lineEditResult->repaint();
}

void PSOParameters::setProgress(const double &ratio)
{
    double tmp = ratio + 0.01;
    ui->progressBar->setValue(tmp*100);
    ui->progressBar->repaint();
}

void PSOParameters::showParameters( std::map<QString,double> &pso,
                                    std::map<QString,double> &de)
{
    //设置pso的参数
    ui->LineEditGroup->setText(QString::number(static_cast<int>(pso["population"]),10));
    ui->LineEditGeneration->setText(QString::number(static_cast<int>(pso["generation"]),10));
    double ratio = pso["w"];
    ui->horizontalSliderWeight->setValue(static_cast<int>(ratio*100));
    ui->LineEditSpeed1->setText(QString::number(pso["c1"],10,2));
    ui->LineEditSpeed2->setText(QString::number(pso["c1"],10,2));
    ui->ComboBoxDimension->setCurrentText(QString::number(static_cast<int>(pso["dimension"])));
    ui->LineEditUp->setText(QString::number(pso["upbounding"],10,2));
    ui->LineEditDown->setText(QString::number(pso["lowbounding"],10,2));

    //设置de的参数
    ui->LineEditGroup_D->setText(QString::number(static_cast<int>(de["population"]),10));
    ui->LineEditGeneration_D->setText(QString::number(static_cast<int>(de["generation"]),10));
    double F = de["F"];
    double CR = de["CR"];
    ui->horizontalSliderFactor_D->setValue(static_cast<int>(F*200));
    ui->horizontalSliderCR_D->setValue(static_cast<int>(CR*100));
    ui->ComboBoxDimension_D->setCurrentText(QString::number(static_cast<int>(de["dimension"])));
    ui->LineEditUp_D->setText(QString::number(de["upbounding"],10,2));
    ui->LineEditDown_D->setText(QString::number(de["lowbounding"],10,2));
}


void PSOParameters::on_LineEditGroup_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
}

void PSOParameters::on_LineEditGroup_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1);
}

void PSOParameters::on_LineEditGroup_editingFinished()
{
    double value = ui->LineEditGroup->text().toDouble();
    emit changeParameter(tr("population"),value, false);
}

void PSOParameters::on_LineEditGeneration_editingFinished()
{
    double value = ui->LineEditGeneration->text().toDouble();
    emit changeParameter(tr("generation"),value, false);
}

void PSOParameters::on_LineEditSpeed1_editingFinished()
{
    double value = ui->LineEditSpeed1->text().toDouble();
    emit changeParameter(tr("c1"),value, false);
}

void PSOParameters::on_LineEditSpeed2_editingFinished()
{
    double value = ui->LineEditSpeed2->text().toDouble();
    emit changeParameter(tr("c2"),value, false);
}

void PSOParameters::on_LineEditUp_editingFinished()
{
    double value = ui->LineEditUp->text().toDouble();
    emit changeParameter(tr("upbounding"),value, false);
}

void PSOParameters::on_LineEditDown_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1);
    Q_UNUSED(arg2);
}

void PSOParameters::on_LineEditDown_editingFinished()
{
    double value = ui->LineEditDown->text().toDouble();
    emit changeParameter(tr("lowbounding"),value, false);
}

void PSOParameters::on_LineEditGroup_D_editingFinished()
{
    double value = ui->LineEditGroup_D->text().toDouble();
    emit changeParameter(tr("population"),value, true);
}

void PSOParameters::on_LineEditGeneration_D_editingFinished()
{
    double value = ui->LineEditGeneration_D->text().toDouble();
    emit changeParameter(tr("generation"),value, true);
}

void PSOParameters::on_LineEditUp_D_editingFinished()
{
    double value = ui->LineEditUp_D->text().toDouble();
    emit changeParameter(tr("upbounding"),value, true);
}

void PSOParameters::on_LineEditDown_D_editingFinished()
{
    double value = ui->LineEditDown_D->text().toDouble();
    emit changeParameter(tr("lowbounding"),value, true);
}

void PSOParameters::on_horizontalSliderWeight_valueChanged(int value)
{
    double ratio = value/100.0;
    ui->labelWeight->setText(QString::number(ratio,10,1));
    emit changeParameter(tr("w"),ratio,false);
}

void PSOParameters::on_ComboBoxDimension_currentTextChanged(const QString &arg1)
{
    int value = arg1.toInt();
    emit changeParameter(tr("dimension"),static_cast<double>(value),false);
}

void PSOParameters::on_horizontalSliderFactor_D_valueChanged(int value)
{
    double ratio = value/200.0;
    ui->labelFactor_D->setText(QString::number(ratio,10,1));
    emit changeParameter(tr("F"),ratio,true);
}

void PSOParameters::on_horizontalSliderCR_D_valueChanged(int value)
{
    double ratio = value/100.0;
    ui->labelCR_D->setText(QString::number(ratio,10,1));
    emit changeParameter(tr("CR"),ratio,true);
}

void PSOParameters::on_ComboBoxDimension_D_currentTextChanged(const QString &arg1)
{
    int value = arg1.toInt();
    emit changeParameter(tr("dimension"),static_cast<double>(value),true);
}

void PSOParameters::on_pushButtonProcess_clicked()
{
    emit beginToProcess(ui->tabWidget->currentIndex());
}

void PSOParameters::on_comboBoxFunction_currentIndexChanged(int index)
{
    int value = index + 1;
    emit changeParameter(tr("function"),value, false);
    emit changeParameter(tr("function"),value, true);
}

void PSOParameters::on_LineEditGeneration_returnPressed()
{
}

#include "Setting.h"
#include "ui_Setting.h"
#include <QMessageBox>
#include "Algorithm/MOP_Algorithm.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    algorithm_nsga = nullptr;
    algorithm_moea = nullptr;
}

Setting::~Setting()
{
    delete ui;
}

void Setting::setParamter(MOP_Algorithm *algorithm)
{
    ui->groupLineEdit->setText(QString::number(algorithm->getGroup()));
    ui->generationLineEdit->setText(QString::number(algorithm->getGeneration()));
    ui->objectComboBox->setCurrentText(QString::number(algorithm->getObjective()));
    ui->dimensionComboBox->setCurrentText(QString::number(algorithm->getDimension()));
}

void Setting::setNsga_II(MOP_Algorithm *nsga)
{
    this->algorithm_nsga = nsga;
    setParamter(algorithm_nsga);
}

void Setting::setMoea_D(MOP_Algorithm *moea)
{
    this->algorithm_moea = moea;
}

void Setting::setProgress(double progress)
{
    ui->progressBar->setValue(progress*100);
}

void Setting::on_pushButton_clicked()
{
    if(!algorithm_nsga || !algorithm_moea)return;
    if(algorithm_moea->isBegin || algorithm_nsga->isBegin){
        QMessageBox::information(this,tr("警告"),tr("当前算法任务尚未结束!"));
        return;
    }
    if(ui->algorithmComboBox->currentText() == "NSGA-II"){
       emit begin(0);
    }
    else if(ui->algorithmComboBox->currentText() == "MOEA/D"){
       emit begin(1);
    }
}

void Setting::on_algorithmComboBox_currentTextChanged(const QString &arg1)
{
    if(!algorithm_nsga || !algorithm_moea)return;
    if(arg1 == "NSGA-II"){
        setParamter(algorithm_nsga);
    }
    else if(arg1 == "MOEA/D"){
        setParamter(algorithm_moea);
    }
}

void Setting::on_groupLineEdit_editingFinished()
{
    if(!algorithm_nsga || !algorithm_moea)return;
    int num = ui->groupLineEdit->text().toInt();
    if(ui->algorithmComboBox->currentText() == "NSGA-II"){
       algorithm_nsga->setGroup(num);
    }
    else if(ui->algorithmComboBox->currentText() == "MOEA/D"){
       algorithm_moea->setGroup(num);
    }
}

void Setting::on_objectComboBox_currentTextChanged(const QString &arg1)
{
    if(!algorithm_nsga || !algorithm_moea)return;
    int num = arg1.toInt();
    if(ui->algorithmComboBox->currentText() == "NSGA-II"){
       algorithm_nsga->setObjective(num);
       setParamter(algorithm_nsga);
    }
    else if(ui->algorithmComboBox->currentText() == "MOEA/D"){
       algorithm_moea->setObjective(num);
       setParamter(algorithm_moea);
    }
}

void Setting::on_dimensionComboBox_currentTextChanged(const QString &arg1)
{
    if(!algorithm_nsga || !algorithm_moea)return;
    problemNum = ui->dimensionComboBox->currentIndex()+1;
//    int num = arg1.toInt();
//    if(ui->algorithmComboBox->currentText() == "NSGA-II"){
//       algorithm_nsga->setDimension(num);
//    }
//    else if(ui->algorithmComboBox->currentText() == "MOEA/D"){
//       algorithm_moea->setDimension(num);
//    }
}

void Setting::on_generationLineEdit_editingFinished()
{
    if(!algorithm_nsga || !algorithm_moea)return;
    int num = ui->generationLineEdit->text().toInt();
    if(ui->algorithmComboBox->currentText() == "NSGA-II"){
       algorithm_nsga->setGeneration(num);
    }
    else if(ui->algorithmComboBox->currentText() == "MOEA/D"){
       algorithm_moea->setGeneration(num);
    }
}

void Setting::on_pushButton_2_clicked()
{
    if(!algorithm_nsga || !algorithm_moea)return;
    if(algorithm_nsga->isBegin){
        algorithm_nsga->shouldStop = true;
    }
    if(algorithm_moea->isBegin){
        algorithm_moea->shouldStop = true;
    }
}

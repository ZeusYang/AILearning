#include "Widget.h"
#include "ui_Widget.h"
#include <QDebug>
#include <iostream>
#include <QRegExp>
#include "Algorithm/Des.h"
#include "Algorithm/AES.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QRegExp regx("[a-zA-Z0-9]{1,8}$");
    QValidator* validator = new QRegExpValidator(regx, this);
    ui->LineEditKey->setValidator(validator);
    ui->LineEditVec->setValidator(validator);

    algorithm = new Des();
    on_LineEditVec_editingFinished();
    on_LineEditKey_editingFinished();
    on_ComboBoxMode_currentIndexChanged(0);
}

Widget::~Widget()
{
    delete ui;
    if(algorithm)delete algorithm;
    algorithm = nullptr;
}

void Widget::on_LineEditVec_editingFinished()
{
    if(algorithm){
        algorithm->SetInitVec(ui->LineEditVec->text());
    }
}

void Widget::on_LineEditKey_editingFinished()
{
    if(algorithm){
        algorithm->SetKey(ui->LineEditKey->text());
    }
}

void Widget::on_pushButtonEncode_clicked()
{
    if(!algorithm)return;
    on_LineEditVec_editingFinished();
    on_LineEditKey_editingFinished();
    QString message = ui->plainTextEditText->toPlainText();
    message = algorithm->EncodeMessage(message);
    if(!message.isEmpty())
        ui->plainTextEditCipher->setPlainText(message);
}

void Widget::on_pushButtonDecode_clicked()
{
    if(!algorithm)return;
    on_LineEditVec_editingFinished();
    on_LineEditKey_editingFinished();
    QString message = ui->plainTextEditCipher->toPlainText();
    message = algorithm->DecodeMessage(message);
    ui->plainTextEditDecode->setPlainText(message);
}

void Widget::on_ComboBoxMode_currentIndexChanged(int index)
{
    if(!algorithm)return;
    algorithm->setMode(index);
}

void Widget::on_ComboBoxAlgorithm_currentIndexChanged(int index)
{
    if(algorithm)delete algorithm;
    algorithm = nullptr;
    if(index == 0){
        algorithm = new Des();
        QRegExp regx("[a-zA-Z0-9]{1,8}$");
        QValidator* validator = new QRegExpValidator(regx, this);
        ui->LineEditKey->setValidator(validator);
        ui->LineEditVec->setValidator(validator);
        ui->LineEditKey->setText(tr("encipher"));
    }
    else if(index == 1){
        algorithm = new AES();
        QRegExp regx("[a-zA-Z0-9]{1,16}$");
        QValidator* validator = new QRegExpValidator(regx, this);
        ui->LineEditKey->setValidator(validator);
        ui->LineEditVec->setValidator(validator);
        ui->LineEditKey->setText(tr("123456789abcdef0"));
        ui->LineEditVec->setText(tr("987654321abcdef0"));
    }
    on_LineEditKey_editingFinished();
    on_LineEditVec_editingFinished();
    on_ComboBoxMode_currentIndexChanged(0);
}

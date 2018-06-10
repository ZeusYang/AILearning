#include "Widget.h"
#include "ui_Widget.h"
#include <QMessageBox>
#include <QDebug>
#include "Algorithm/Hill.h"
#include "Algorithm/Affine.h"
#include "Algorithm/Caesar.h"
#include "Algorithm/Vigenere.h"
#include "Algorithm/Playfair.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    algorithm = new Caesar();
}

Widget::~Widget()
{
    delete ui;
    if(algorithm)delete algorithm;
    algorithm = nullptr;
}

void Widget::on_pushButtonEncode_clicked()
{
    if(!algorithm)return;
    QString message = ui->plainTextEditText->toPlainText();
    if(message.isEmpty()){
        QMessageBox::warning(this,tr("警告"),
                             tr("加密对象不能为空!!!"));
        return;
    }
    // 加密
    message = algorithm->EncodeMessage(message);
    // 输出显示
    ui->plainTextEditCiper->setPlainText(message);
}

void Widget::on_pushButtonDecode_clicked()
{
    if(!algorithm)return;
    QString message = ui->plainTextEditCiper->toPlainText();
    if(message.isEmpty()){
        QMessageBox::warning(this,tr("警告"),
                             tr("解密对象不能为空!!!"));
        return;
    }
    // 解密
    message = algorithm->DecodeMessage(message);
    // 输出显示
    ui->plainTextEditDecoded->setPlainText(message);
}

void Widget::on_ComboBoxCiper_currentIndexChanged(int index)
{
    if(algorithm)delete algorithm;
    algorithm = nullptr;
    if(index == 0){
        algorithm = new Caesar();
    }
    else if(index == 1){
        algorithm = new Playfair();
    }
    else if(index == 2){
        algorithm = new Hill();
    }
    else if(index == 3){
        algorithm = new Vigenere();
    }
    else if(index == 4){
        algorithm = new Affine();
    }
    ui->plainTextEditDecoded->clear();
    ui->plainTextEditCiper->clear();
}

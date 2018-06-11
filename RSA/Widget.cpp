#include "Widget.h"
#include <QRegExp>
#include <QMessageBox>
#include "ui_Widget.h"
#include "Algorithm/RSA_Encryption.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    algorithm = new RSA_Encryption();

    QIntValidator* validator = new QIntValidator(32,256, this);
    ui->LineEditLength->setValidator(validator);
    ui->LineEditLength->setText("32");
    connect(algorithm,&RSA_Encryption::SendProgress,
            this,&Widget::GetProgress);
}

Widget::~Widget()
{
    delete ui;
    if(algorithm) delete algorithm;
    algorithm = nullptr;
}

void Widget::on_pushButtonGenerate_clicked()
{
    QString str = ui->LineEditLength->text();
    int num = str.toInt();
    algorithm->Initial(num);
    ui->LineEditPublic->setText(QString(algorithm->GetPublicKey()));
    ui->LineEditPrivate->setText(QString(algorithm->GetPrivateKey()));
}

void Widget::on_pushButtonEncode_clicked()
{
    if(!algorithm)return;
    if(!algorithm->GenearteKey()){
       QMessageBox::warning(this,tr("警告"),
                            tr("尚未生成密钥!!!"));
       return;
    }
    QString message = ui->plainTextEditText->toPlainText();
    if(message.isEmpty())return;
    message = algorithm->EncodeMessage(message);
    ui->plainTextEditCipher->setPlainText(message);
}

void Widget::on_pushButtonDecode_clicked()
{
    if(!algorithm)return;
    if(!algorithm->GenearteKey()){
       QMessageBox::warning(this,tr("警告"),
                            tr("尚未生成密钥!!!"));
       return;
    }
    QString message = ui->plainTextEditCipher->toPlainText();
    if(message.isEmpty())return;
    message = algorithm->DecodeMessage(message);
    ui->plainTextEditDecode->setPlainText(message);
}

void Widget::GetProgress(double progress)
{
    ui->progressBar->setValue(100*progress);
    qApp->processEvents();
}

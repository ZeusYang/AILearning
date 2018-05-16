#include "curvedialog.h"
#include "ui_curvedialog.h"
#include "psoparameters.h"
#include <QHBoxLayout>
#include <QDebug>

CurveDialog::CurveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CurveDialog)
{
    ui->setupUi(this);
    //非模态对话框
    this->setModal(false);
    //布局
    setting = new PSOParameters(this);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(setting);
    this->setLayout(layout);
}

CurveDialog::~CurveDialog()
{
    delete ui;
}

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}
class RSA_Encryption;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButtonGenerate_clicked();

    void on_pushButtonEncode_clicked();

    void on_pushButtonDecode_clicked();


    void GetProgress(double progress);

private:
    Ui::Widget *ui;
    RSA_Encryption *algorithm;
};

#endif // WIDGET_H

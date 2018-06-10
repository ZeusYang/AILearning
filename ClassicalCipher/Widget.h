#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Algorithm/Encryption.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_pushButtonEncode_clicked();

    void on_pushButtonDecode_clicked();

    void on_ComboBoxCiper_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
    Encryption *algorithm;
};

#endif // WIDGET_H

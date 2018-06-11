#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}
class Encryption;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_LineEditVec_editingFinished();

    void on_LineEditKey_editingFinished();

    void on_pushButtonEncode_clicked();

    void on_pushButtonDecode_clicked();

    void on_ComboBoxMode_currentIndexChanged(int index);

    void on_ComboBoxAlgorithm_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
    Encryption *algorithm;
};

#endif // WIDGET_H

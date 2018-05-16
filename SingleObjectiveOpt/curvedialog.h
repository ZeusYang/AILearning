#ifndef CURVEDIALOG_H
#define CURVEDIALOG_H

#include <QDialog>

namespace Ui {
class CurveDialog;
}
class PSOParameters;
class CurveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CurveDialog(QWidget *parent = 0);
    ~CurveDialog();

    PSOParameters *setting;

private:
    Ui::CurveDialog *ui;
};

#endif // CURVEDIALOG_H

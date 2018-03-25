#ifndef WRITEBOARD_H
#define WRITEBOARD_H

#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QDebug>
#include <vector>
#include <iostream>

#define PIXEL_WIDTH 20
#define INDEX(x) x/PIXEL_WIDTH
#define POINT(x) x*PIXEL_WIDTH

class WriteBoard : public QLabel
{
public:
    explicit WriteBoard(QWidget *parent = NULL,int w = 28,int h = 28);

    ~WriteBoard();

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void clear();

    double* GetMatrix();

    void SetMatrix(double *target,int widt,int height);

    void ShowPixel();

private:
    double *pixel;
    int widths,heights;
    QPixmap background;
    bool beginWrite;
    std::vector<QPointF>lightIt;

    int TransIndex(int r,int c);
};

#endif // WRITEBOARD_H

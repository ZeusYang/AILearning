#include "writeboard.h"
#include <time.h>

WriteBoard::WriteBoard(QWidget *parent,int w,int h)
        :QLabel(parent),widths(w),heights(h)
{
    pixel = new double [widths*heights];
    memset(pixel,0.0f,sizeof(pixel));
    background.load(":/pixels/bg.jpg");
    this->resize(widths*PIXEL_WIDTH,heights*PIXEL_WIDTH);
    beginWrite = false;
}


WriteBoard::~WriteBoard()
{
    clear();
    delete [] pixel;
    pixel = NULL;
}

void WriteBoard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    //draw background
    QRect target(0,0,this->width(),this->height());
    QRect resource(0,0,1024,755);
    painter.drawPixmap(target,background,resource);

    //draw grids
    int wlen = widths*PIXEL_WIDTH,hlen = heights*PIXEL_WIDTH;
    for(int x = 0;x < heights+1;x ++){
        QPointF start(0,x*PIXEL_WIDTH);
        QPointF end(wlen,x*PIXEL_WIDTH);
        painter.drawLine(start,end);
    }

    for(int y = 0;y < widths+1;y ++){
        QPointF start(y*PIXEL_WIDTH,0);
        QPointF end(y*PIXEL_WIDTH,hlen);
        painter.drawLine(start,end);
    }

    int len = lightIt.size();
    painter.setPen(QPen(Qt::red,2));
    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    for(int x = 0;x < len;x ++){
        QRect area(lightIt[x].x(),lightIt[x].y(),
                   PIXEL_WIDTH,PIXEL_WIDTH);
        painter.drawRect(area);
    }
}

void WriteBoard::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(!beginWrite){
            clear();
            beginWrite = true;
            srand(time(NULL));
        }
    }
}

void WriteBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        //if(beginWrite)beginWrite = false;
    }
}

void WriteBoard::mouseMoveEvent(QMouseEvent *event)
{
    if(beginWrite){
        int c = INDEX(event->pos().x());
        int r = INDEX(event->pos().y());
        QPointF record(POINT(c),POINT(r));
        lightIt.push_back(record);
        //QPointF left(POINT(c-1),POINT(r));
        //QPointF top(POINT(c),POINT(r-1));

        pixel[TransIndex(r,c)] = 1.0f;
        if(c-1>=0){
            pixel[TransIndex(r,c-1)] = 1.0f;
            QPointF left((c-1)*PIXEL_WIDTH,POINT(r));
            lightIt.push_back(left);
            //qDebug() << (c-1) << ":" << (c-1)*PIXEL_WIDTH << "-" << POINT(r);
        }
        if(r-1>=0){
            pixel[TransIndex(r-1,c)] = 1.0f;
            QPointF top(POINT(c),(r-1)*PIXEL_WIDTH);
            lightIt.push_back(top);
        }
        if(c+1<=widths){
            pixel[TransIndex(r,c+1)] = 1.0f;
            QPointF right((c+1)*PIXEL_WIDTH,(r)*PIXEL_WIDTH);
            lightIt.push_back(right);
        }
        /*if(r+1<=heights && (rand()%100)>=50){
            pixel[TransIndex(r+1,c)] = 1.0f;
            QPointF down(POINT(c),(r+1)*PIXEL_WIDTH);
            lightIt.push_back(down);
        }*/
        this->repaint();
    }
}

int WriteBoard::TransIndex(int r, int c)
{
    return r*widths+c;
}

void WriteBoard::clear()
{
    beginWrite = false;
    lightIt.clear();
    for(int r = 0;r < heights;r ++){
        for(int c = 0;c < widths;c ++){
            pixel[TransIndex(r,c)] = 0.0f;
        }
    }
    this->repaint();
}

double* WriteBoard::GetMatrix()
{
    return pixel;
}

void WriteBoard::SetMatrix(double *target,int width,int height)
{
    clear();
    for(int x = 0;x < width;x ++){
        for(int y = 0;y < height;y ++){
            if(target[x*width+y] == 1.0){
                QPointF record(POINT(y),POINT(x));
                lightIt.push_back(record);
                pixel[x*width+y] = 1.0f;
            }
        }
    }
    this->repaint();
}

void WriteBoard::ShowPixel()
{
    using namespace std;
    for(int x = 0;x < widths;x ++){
        for(int y = 0;y < heights;y ++){
            if(pixel[x*widths+y]==1.0f)cout << pixel[x*widths+y];
            else cout << " ";
        }
        cout << endl;
    }
}

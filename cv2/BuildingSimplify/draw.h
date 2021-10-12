#ifndef DRAW_H
#define DRAW_H

#include <QtGui>
#include <QWidget>
#include <vector>

class Draw : public QWidget
{
    private:
        std::vector <QPoint> points;
        QPolygon ch, er;

    public:
        explicit Draw(QWidget *parent = nullptr);
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void clear();
        std::vector<QPoint> getPoints(){return points;};
        void setCh(QPolygon &ch_){ch=ch_;};


};

#endif // DRAW_H



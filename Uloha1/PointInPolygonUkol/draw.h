#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <QtGui>
#include "algorithms.h"

class Draw : public QWidget
{
    Q_OBJECT

private:
    std::vector<QPoint> vertices;
    QPoint q;
    bool add_vertex;
    double x,y;
    std::vector<QPolygonF> pol;
    std::vector<int> result;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void clear();
    void changeStatus(){add_vertex=!add_vertex;};
    QPointF getPoint(){return q;};
    std::vector<QPolygonF> getPolygon(){return pol;};
    void loadFile(std::string &path);
    void setX(double x_){x=x_;};
    void setY(double y_){y=y_;};

signals:

public slots:
};

#endif // DRAW_H

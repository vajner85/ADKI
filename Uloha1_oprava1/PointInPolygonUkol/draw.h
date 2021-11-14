#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <QtGui>
#include "algorithms.h"
#include <QString>

class Draw : public QWidget
{
    Q_OBJECT

private:
    QPoint q;
    boolean enabledraw;

    double x,y;
    std::vector<QPolygonF> pol;
    std::vector<QPolygonF> polcol;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void clear();
    void changeStatus(){enabledraw=!enabledraw;};
    QPointF getPoint(){return q;};
    std::vector<QPolygonF> getPolygon(){return pol;};
    void loadFile(std::string &path);
    void setX(double x_){x=x_;};
    void setY(double y_){y=y_;};

    void setPolcol(QPolygonF &polcol_){polcol.push_back(polcol_);};

signals:

public slots:
};

#endif // DRAW_H

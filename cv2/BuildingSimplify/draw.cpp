#include "draw.h"

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::paintEvent(QPaintEvent *event)
{
    QPainter qp(this);
    qp.begin(this);

    int r=4;
    QPolygon pol;
    //Draw points
    for (int i=0; i < points.size(); i++)
    {
        qp.drawEllipse(points[i].x()-r,points[i].y()-r,2*r,2*r);
        pol.append(points[i]);
    }

    //Draw polygon
    qp.setBrush(Qt::yellow);
    qp.drawPolygon(pol);

    qp.end();
}
void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get coords
    int x=event->pos().x();
    int y=event->pos().y();

    //Create point
    QPoint p(x,y);
    points.push_back(p);

    //Update screen
    repaint();
}

void Draw::clear()
{
    points.clear();
    ch.clear();
    er.clear();
    repaint();
}

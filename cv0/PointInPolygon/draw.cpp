#include "draw.h"
#include <QtGui>


Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::paintEvent(QPaintEvent *event)
{
    //Create graphic object
    QPainter painter(this);
    painter.begin(this);

    //create polygon
    QPolygon pol;

    //convert vector to polygon
    for (int i =0;i<vertices.size(); i++)
    {
    pol.append(vertices[i]);
    }

    //draw polygon
    painter.drawPolygon(pol);

    //Improvements
    //  for(Qpoint vertex:vertices)
    //      pol.append(vertex);

    painter.end();

}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get cursor coordinates
    int x=event->pos().x();
    int y=event->pos().y();

    //Create point
    QPoint p(x,y);

    //Add point to vector
    vertices.push_back(p);


    repaint();

}

void Draw::clear()
{
    vertices.clear();
    repaint();

}

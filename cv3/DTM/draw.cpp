#include "draw.h"
#include <stdlib.h>

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    //Initialize rand number generator
    srand(time(NULL));
}

void Draw::paintEvent(QPaintEvent *event)
{
    QPainter qp(this);
    qp.begin(this);

    //Draw points
    int r=4;
    QPolygon pol;

    for (int i=0; i<points.size(); i++)
    {
        qp.drawEllipse(points[i].x()-r,points[i].y()-r,2*r,2*r);
        pol.append(QPoint(points[i].x(), points[i].y()));
    }

    //Draw triangulation
    for(Edge e : dt)
    {
        //Get start point, get end point
        QPoint3D s_point = e.getStart();
        QPoint3D e_point = e.getEnd();

        //Draw line
        qp.drawLine(s_point,e_point);
    }

    //Draw contour lines
    for(Edge c: contours)
    {
        //Get start point, get end point
        QPoint3D s_point = c.getStart();
        QPoint3D e_point = c.getEnd();

        //Draw line
        qp.drawLine(s_point,e_point);
    }

    //Draw slope
    double k = 255/M_PI;
    for(Triangle t:triangles)
    {
        //Get vertice
        QPoint3D p1 = t.getP1();
        QPoint3D p2 = t.getP2();
        QPoint3D p3 = t.getP3();

        //get slope
        double slope = t.getSlope();

        //Convert to color
        int col = 255-slope*k;
        QColor color(col,col,col);

        //Set pen & brush
        qp.setBrush(color);
        qp.setPen(color);

        //Create polygon
        QPolygon pol;
        pol.push_back(QPoint(p1.x(),p1.y()));
        pol.push_back(QPoint(p2.x(),p2.y()));
        pol.push_back(QPoint(p3.x(),p3.y()));

        //Draw oylgon
        qp.drawPolygon(pol);
    }
    qp.end();
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get coordinates
    int x = event->pos().x();
    int y = event->pos().y();

    int z = rand()%1000;

    //Create point
    QPoint3D p(x,y,z);

    //Add point to the vector
    points.push_back(p);

    //Update screen
    repaint();
}

void Draw::clear()
{
    points.clear();
    repaint();
}

void Draw::clearDT()
{
    dt.clear();
    repaint();
}


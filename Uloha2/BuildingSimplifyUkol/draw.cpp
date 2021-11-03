#include "draw.h"
#include <QtGui>
#include <fstream>
#include <QWidget>
#include <fstream>
#include <iostream>

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::paintEvent(QPaintEvent *event)
{
    QPainter qp(this);
    qp.begin(this);


    //Path setter
    QPainterPath path;

    //Draw polygon
        for(int i = 0; i < pol.size(); i++)
        {
            QPolygon poly;
            poly.append(pol[i]);
            //Draw polygon
            qp.setBrush(Qt::yellow);
            qp.drawPolygon(poly);
        }


    //Draw convex hull
    qp.setBrush(Qt::NoBrush);
    qp.setPen(Qt::red);
    qp.drawPolygon(ch);

    //Draw enclosing rectangle
    qp.setBrush(Qt::NoBrush);
    qp.setPen(Qt::green);
    qp.drawPolygon(er);

    qp.end();
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get coordinates
    int x = event->pos().x();
    int y = event->pos().y();

    //Create point
    QPoint p(x,y);

    //Add point to the vector
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

void Draw::loadFile(std::string &path)
{
    int id,i;
    double fid;
    double x;
    double y;
    QPolygon poly;
    QPoint p;
    int fid_min=0;

    //Loading files
    std::ifstream file(path);

   if (file.is_open())
      {
        while (file >> x >> y >> id >> fid)
        {

            if (fid == fid_min)
            {
                // pushing back the current polygon
                p.setX(x);
                p.setY(y);
                poly.push_back(p);
            }
            else
            {
                // creating new polygon
                pol.push_back(poly);
                poly.clear();
                // adding of a new point to the new polygon
                p.setX(x);
                p.setY(y);
                poly.push_back(p);
                fid_min = fid;
            }
        }
            //Saving
            pol.push_back(poly);

            //Erasing of all the polygons
            poly.clear();

     //Closing file
     file.close();
    }
}

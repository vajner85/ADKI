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
    for(int i = 0; i < pols.size(); i++)
    {
        QPolygon poly;
        poly.append(pols[i]);

        //Draw polygon
        qp.setBrush(Qt::yellow);
        qp.drawPolygon(poly);
    }


    //Draw convex hull
    qp.setBrush(Qt::NoBrush);
    qp.setPen(Qt::red);
    //qp.drawPolygon(ch_v);
    if (ch_v.size() > 0)
            for (QPolygon chull : ch_v)
                qp.drawPolygon(chull);

    //Draw enclosing rectangle
    qp.setBrush(Qt::NoBrush);
    qp.setPen(Qt::green);
    //qp.drawPolygon(er);
    if (er_v.size() > 0)
            for (QPolygon enrect : er_v)
                qp.drawPolygon(enrect);

    qp.end();
}

//void Draw::mousePressEvent(QMouseEvent *event)
//{}

void Draw::clear()
{
    points.clear();
    pols.clear();
    ch.clear();
    er.clear();
    er_v.clear();
    ch_v.clear();

    repaint();
}

void Draw::loadFile(std::string &path)
{
    int id, fid = -1, fid_min = fid;
    double x, y;
    QPolygon pol;


    //Loading files
    std::ifstream file(path);

    if (file.is_open())
    {
        //Read line
        while (file >> x >> y >> id >> fid)
        {
            //Moving points to canvas viewed window
            //x=(-x-740000)/3;
            //y=(-y-1043000)/3;

            //Same ID, intermediate point
            if (fid == fid_min || fid_min == -1)
            {
                //Add point to the list
                pol.push_back(QPoint(x,y));
            }

            //ID has changed
            else
            {
                //Add old polygon to the list
                pols.push_back(pol);

                //Clear the polygon
                pol.clear();

                //Add new point
                pol.push_back(QPoint(x, y));
            }

            fid_min = fid;
        }

        //Add last polygon to the list
        pols.push_back(pol);

        //Closing file
        file.close();
    }
}

#include "draw.h"
#include <QtGui>
#include <fstream>
#include <QWidget>
#include <fstream>

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    enabledraw = false;
    q.setX(-100);
    q.setY(-100);
}

void Draw::paintEvent(QPaintEvent *event)
{
    // Create graphic object
    QPainter painter(this);
    painter.begin(this);

    //Path setter
    QPainterPath path;

    //Draw polygon
        for(int i = 0; i < pol.size(); i++)
        {
            QPolygonF poly = pol[i];
            painter.drawPolygon(poly);
        }
    //Draw point
    painter.drawEllipse(q.x()-4,q.y()-4,8,8);

    painter.end();
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get cursor coordinates
    int x = event->pos().x();
    int y = event->pos().y();


    if (enabledraw)
    {
        //Modify coord q
        q.setX(x);
        q.setY(y);
    }
    //Repaint screen
    repaint();
}

void Draw::clear()
{
    //Clear and repaint
    pol.clear();
    repaint();
}

void Draw::loadFile(std::string &path)
{
    int id,i;
    double x;
    double y;
    QPolygonF poly;
    QPointF p;

    //Loading files
    std::ifstream file(path);

   if (file.is_open())
      {
        while (file >> id >> x >> y )
        {
            if (i == id)
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
                i = 1;
            }
          i++;
          }
            //Saving
            pol.push_back(poly);

            //Erasing of all the polygons
            poly.clear();

     //Closing file
     file.close();
    }
}

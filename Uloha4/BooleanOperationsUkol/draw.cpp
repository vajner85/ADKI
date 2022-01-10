#include "draw.h"
#include <fstream>
#include <iostream>


Draw::Draw(QWidget *parent) : QWidget(parent)
{
    addA = true;
}

void Draw::paintEvent(QPaintEvent *event)
{
    QPainter qp(this);
    qp.begin(this);

    //Path setter
    QPainterPath path;

    //Draw polygons
    qp.setPen(Qt::yellow);
    drawPolygon(A, qp);
    qp.setPen(Qt::green);
    drawPolygon(B, qp);

    //Draw edges
    qp.setPen(Qt::red);
    for(Edge e:res)
        qp.drawLine(e.getStart(), e.getEnd());

    qp.end();
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get coordinates
    int x = event->pos().x();
    int y = event->pos().y();

    //Create point
    QPointFBO p(x,y);

    //Add point to A, B
    if (addA)
        A.push_back(p);
    else
        B.push_back(p);

    //Update screen
    repaint();
}

void Draw::drawPolygon(TPolygon &polygon, QPainter &qp)
{
    //Draw polygon on canvas
    int r=4;
    QPolygon pol;

    //Convert polygon to QPolygon
    for (int i=0; i<polygon.size(); i++)
    {
       qp.drawEllipse(polygon[i].x()-r,polygon[i].y()-r,2*r,2*r);
       pol.append(QPoint(polygon[i].x(),polygon[i].y()));
    }

    //Draw polygon
    qp.drawPolygon(pol);
}

void Draw::loadFile(std::string &path)
{
    int id, i;
    double x, y;
    TPolygon A, B;
    TPolygon poly;
    std::vector<TPolygon>pol;

    //Loading files
    std::ifstream file(path);

    if (file.is_open())
    {
        //Read line
        while (file >> id >> y >> x)
        {
            //Moving points to canvas viewed window
            //x=(-y-740000)/3;
            //y=(-x-1043000)/3;

            //Same ID, intermediate point
            if (i==id)
            {
                //Add point to the list
               poly.push_back(QPointFBO(x,y));
            }

            //ID has changed
            else
            {
                // creating new polygon
                pol.push_back(poly);
                poly.clear();
                //Add new point
                poly.push_back(QPointFBO(x, y));
                i=1;
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

    A = pol[1];
    B = pol[2];
    repaint();
}

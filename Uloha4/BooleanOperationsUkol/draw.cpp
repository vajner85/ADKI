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
    double x, y, yy, m;

    double xmin(10e16), ymin(10e16);
    double xmax(0),ymax(0);

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
            if(x<0 && y<0)
            {
                yy=x;
                x=-y;
                y=-yy;
             }

            //Searching for min,max values of x,y
            if(x<xmin)
            {xmin=x;}
            if(x>xmax)
            {xmax=x;}

            if(y<ymin)
            {ymin=y;}
            if(y>ymax)
            {ymax=y;}

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

    //Count real coord differences
    double xdif=xmax-xmin;
    double ydif=ymax-ymin;

    //Count q widget coord differences
    double xd=xdif/1000;
    double yd=ydif/650;

    //Setting correct transformation value
    if (xd>yd)
        m=xd*1.1;
    else
        m=yd*1.1;

    //Transforming dataset to canvas
    for(int i=0; i<A.size();i++)
    {
        A[i].setX((A[i].x()/m));
        A[i].setY((A[i].y()/m));
    }

    //Transforming dataset to canvas
    for(int i=0; i<B.size();i++)
    {
        B[i].setX((B[i].x()/m));
        B[i].setY((B[i].y()/m));
    }

    //Move set to full window
    //Computing virtual point on x,y min with canvas coords
    double xmean=xmin/m;
    double ymean=ymin/m;

    //Computing differences in axes from canvas start point
    double xmeandif=0-xmean+11;
    double ymeandif=0-ymean+11;

    //Moving coords start point to (0,0)
    for(int i=0; i<A.size();i++)
    {
        A[i].setX((A[i].x())+xmeandif);
        A[i].setY((A[i].y())+ymeandif);
    }

    //Moving coords start point to (0,0)
    for(int i=0; i<B.size();i++)
    {
        B[i].setX((B[i].x())+xmeandif);
        B[i].setY((B[i].y())+ymeandif);
    }
}

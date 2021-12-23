#include "draw.h"
#include <stdlib.h>
#include <QtGui>
#include <fstream>
#include <QWidget>
#include <fstream>
#include <iostream>
#include <cmath>



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

    if (meth==TRUE){
    //Draw slope
    double k = 255/M_PI;
    for(Triangle t:triangles)
    {
        //Get vertice
        QPoint3D p1 = t.getP1();
        QPoint3D p2 = t.getP2();
        QPoint3D p3 = t.getP3();

        if (greycol == TRUE)
        {
        //get slope
        double slope = t.getSlope();

        //Convert to color
        int col = 255-slope*k;
        QColor color(col,col,col);

        //Set pen & brush
        qp.setBrush(color);
        qp.setPen(color);
        }

        if (colors == TRUE)
        {
        //get slope
        double slope = t.getSlope();

        //Convert to color
        int col = 255-slope*k;
        if((col >= 0) && (col <=40))
            {qp.setBrush(QColor(255,69,0));
             //qp.setPen(QColor(255,69,0));}
             qp.setPen(QColor(col,col,col));}
        else if ((col > 40) && (col <=80))
            {qp.setBrush(QColor(255,99,71));
             //qp.setPen(QColor(255,99,71));}
            qp.setPen(QColor(col,col,col));}
        else if ((col > 80) && (col <=100))
            {qp.setBrush(QColor(255,127,80));
             //qp.setPen(QColor(255,127,80));}
             qp.setPen(QColor(col,col,col));}
        else if ((col > 100) && (col <=120))
            {qp.setBrush(QColor(255,140,0));
             //qp.setPen(QColor(255,140,0));}
             qp.setPen(QColor(col,col,col));}
        else if ((col > 120) && (col <=160))
            {qp.setBrush(QColor(255,165,0));
             //qp.setPen(QColor(255,165,0));}
             qp.setPen(QColor(col,col,col));}
        else if ((col > 160) && (col <=200))
            {qp.setBrush(QColor(255,190,0));
            //qp.setPen(QColor(255,190,0));}
            qp.setPen(QColor(col,col,col));}
        else if ((col > 200) && (col <=255))
            {qp.setBrush(QColor(255,215,0));
            //qp.setPen(QColor(255,215,0));}
            qp.setPen(QColor(col,col,col));}
        }

        //Create polygon
        QPolygon pol;
        pol.push_back(QPoint(p1.x(),p1.y()));
        pol.push_back(QPoint(p2.x(),p2.y()));
        pol.push_back(QPoint(p3.x(),p3.y()));

        //Draw poylgon
        qp.drawPolygon(pol);
    }
    } else if (meth == FALSE){
    //Draw exposition
    double k = 255/M_PI;
    for(Triangle t:triangles)
    {
        //Get vertice
        QPoint3D p1 = t.getP1();
        QPoint3D p2 = t.getP2();
        QPoint3D p3 = t.getP3();

        if (greycol == TRUE)
        {
        //get exposition
        double expo = t.getExposition();

        //Convert to color
        int col = 255-expo*k;
        QColor color(col,col,col);

        //Set pen & brush
        qp.setBrush(color);
        qp.setPen(color);
        }

        if (colors == TRUE)
        {
        //get exposition
        double expo = t.getExposition();

        //Convert to color
        int col = 255-expo*k;
        if((col >= 0) && (col <=40))
            {qp.setBrush(QColor(255,69,0));
             //qp.setPen(QColor(255,69,0));}
             qp.setPen(QColor(col,col,col));}
        else if ((col > 40) && (col <=80))
            {qp.setBrush(QColor(255,99,71));
             //qp.setPen(QColor(255,99,71));}
            qp.setPen(QColor(col,col,col));}
        else if ((col > 80) && (col <=100))
            {qp.setBrush(QColor(255,127,80));
             //qp.setPen(QColor(255,127,80));}
             qp.setPen(QColor(col,col,col));}
        else if ((col > 100) && (col <=120))
            {qp.setBrush(QColor(255,140,0));
             //qp.setPen(QColor(255,140,0));}
             qp.setPen(QColor(col,col,col));}
        else if ((col > 120) && (col <=160))
            {qp.setBrush(QColor(255,165,0));
             //qp.setPen(QColor(255,165,0));}
             qp.setPen(QColor(col,col,col));}
        else if ((col > 160) && (col <=200))
            {qp.setBrush(QColor(255,190,0));
            //qp.setPen(QColor(255,190,0));}
            qp.setPen(QColor(col,col,col));}
        else if ((col > 200) && (col <=255))
            {qp.setBrush(QColor(255,215,0));
            //qp.setPen(QColor(255,215,0));}
            qp.setPen(QColor(col,col,col));}
        }

        //Create polygon
        QPolygon pol;
        pol.push_back(QPoint(p1.x(),p1.y()));
        pol.push_back(QPoint(p2.x(),p2.y()));
        pol.push_back(QPoint(p3.x(),p3.y()));

        //Draw poylgon
        qp.drawPolygon(pol);
    }
    }

    //Draw main contour lines
    QPen q2(Qt::gray, 2);
    qp.setPen(q2);

    for (int i = 0; i < contoursmain.size(); i++)
    {
        qp.drawLine(contoursmain[i].getStart(), contoursmain[i].getEnd());
    }

    //Draw contour labels
     QPen m(Qt::gray,1);
     qp.setPen(m);

     for (int i = 0; i < contourslabel.size(); i++)
        { Edge one_contour = contourslabel[i];
         QPoint3D label_point1 = one_contour.getStart();
         QPoint3D label_point2 = one_contour.getEnd();
         QPointF label_point;
         label_point.setX((label_point1.x() + label_point2.x()) / 2);
         label_point.setY((label_point1.y() + label_point2.y()) / 2);
         double z = label_point1.getZ();
         QString z_string = QString::number(z);
         qp.drawText(label_point, z_string);
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
    triangles.clear();
    contours.clear();
    contoursmain.clear();
    contourslabel.clear();
    repaint();
}

void Draw::clearDT()
{
    dt.clear();
    repaint();
}

void Draw::loadFile(std::string &path)
{
    double x, y, z, m, yy;
    double xmin(10e16), ymin(10e16);
    double xmax(0),ymax(0);
    std::vector<QPoint3D> pointss;

    //Loading files
    std::ifstream file(path);


    if (file.is_open())
    {
        //Read line
        while (file >> y >> x >> z)
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

            //Add point to the list
            pointss.push_back(QPoint3D (x,y,z));
        }

        //Save vector
        points=pointss;

        //Closing file
        file.close();
    }

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
    for(int i=0; i<points.size();i++)
    {
        points[i].setX((points[i].x()/m));
        points[i].setY((points[i].y()/m));
    }

    //Move set to full window
    //Computing virtual point on x,y min with canvas coords
    double xmean=xmin/m;
    double ymean=ymin/m;

    //Computing differences in axes from canvas start point
    double xmeandif=0-xmean+11;
    double ymeandif=0-ymean+11;

    //Moving coords start point to (0,0)
    for(int i=0; i<points.size();i++)
    {
        points[i].setX((points[i].x())+xmeandif);
        points[i].setY((points[i].y())+ymeandif);
    }
}

#include "draw.h"
#include <QtGui>
#include <fstream>

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    q.setX(-100);
    q.setY(-100);
    add_vertex = true;
}

void Draw::paintEvent(QPaintEvent *event)
{
    // Create graphic object
    QPainter painter(this);
    painter.begin(this);

    //Create new polygon
    QPolygon pol;

    //Setting path
    QPainterPath path;

    //Draw loaded polygons
        for(int i = 0; i < polygons.size(); i++)
        {
            QPolygonF poly = polygons[i];
            painter.drawPolygon(poly);
        }

    //Draw point
    painter.drawEllipse(q.x()-4,q.y()-4,8,8);


    //Improvements
    //for( QPoint vertex : vertices)
    //    pol.append(vertex);

    painter.end();
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get cursor coordinates
    int x = event->pos().x();
    int y = event->pos().y();

    //Modify coord q

       q.setX(x);
       q.setY(y);

    //Repaint screen
    repaint();
}

void Draw::clear()
{
    //Clear and repaint
    vertices.clear();
    repaint();
}

void Draw::loadFile(std::string &path)
{
    int id;
    double x;
    double y;
    QPolygonF polygon;
    QPointF p;

    //Loading files
    std::ifstream file(path);

    if (file.is_open())
    {
        while (file >> id >> x >> y)
        {
            p.setX(x);
            p.setY(y);
            polygon.push_back(p);
        }
    }
        polygons.push_back(polygon);
        file.close();
}

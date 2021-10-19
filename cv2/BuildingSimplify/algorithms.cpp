#include "algorithms.h"
#include <cmath>
#include "sortbyy.h"


Algorithms::Algorithms()
{

}

double Algorithms::get2LinesAngle(QPoint &p1, QPoint &p2, QPoint &p3, QPoint &p4)
{
    //Compute angle formed by two lines

    //Coordinate differences
    double ux=p2.x()-p1.x();
    double uy=p2.y()-p1.y();

    double vx=p4.x()-p3.x();
    double vy=p4.y()-p3.y();

    //Dot product
    double dp=ux*vx+uy*vy;

    //Norms
    double nu = sqrt(ux*ux + uy*uy);
    double nv = sqrt(vx*vx + vy*vy);

    //Angle
    return fabs(acos(dp/(nu*nv)));
}

QPolygon Algorithms::cHull (std::vector <QPoint> &points)
{
    QPolygon ch;

    //Sort points by y
    std::sort(points.begin(),points.end(),sortByY());

    //Find pivot
    QPoint q=points[0];

    //Add pivot to convex hull
    ch.append(q);

    //Create pj, pjj
    QPoint pj = q;
    QPoint pjj(0,q.y());

    do
    {
        int i_max = -1;
        double om_max = 0;
        //Find next point
        for (int i = 0; i<points.size(); i++)
        {
            double om = get2LinesAngle(pj, pjj, pj, points[i]);

            //Update maximum
            if (om > om_max)
            {
                om_max = om;
                i_max = i;
            }
        }

        //dd point to convex hull
        ch.append(points[i_max]);

        //Update points to next ones
        pjj=pj;
        pj=points[i_max];

    } while (pj != q);

    return ch;
}

std::vector<QPoint> Algorithms::rotate(std::vector<QPoint> &points, double sigma)
{
    //Rotate dataset by angle
    std::vector<QPoint> r_points;

    for(int i=0; i<points.size(); i++)
    {
        //Rotated coords
        double x_r=points[i].x()*cos(sigma) - points[i].y()*sin(sigma);
        double y_r=points[i].x()*sin(sigma) + points[i].y()*cos(sigma);

        //Create point
        QPoint p(x_r,y_r);
        r_points.push_back(p);
    }
    return r_points;
}

std::tuple<std::vector<QPoint>, double> Algorithms::minMaxBox(std::vector<QPoint> &points)
{
    //Return vertices of minmaxbox and its area
    double area=0;







}

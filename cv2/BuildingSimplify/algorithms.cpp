#include "algorithms.h"
#include <cmath>
#include "sortbyy.h"
#include "sortbyx.h"

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

    //Return min,max vertices
    QPoint px_min=*std::min_element(points.begin(),points.end(), sortByX());
    QPoint px_max=*std::max_element(points.begin(),points.end(), sortByX());

    QPoint py_min=*std::min_element(points.begin(),points.end(), sortByY());
    QPoint py_max=*std::max_element(points.begin(),points.end(), sortByY());

    //Create minmaxbox vertices
    QPoint v1(px_min.x(),py_min.y());
    QPoint v2(px_max.x(),py_min.y());
    QPoint v3(px_max.x(),py_max.y());
    QPoint v4(px_min.x(),py_max.y());

    //Create minmaxbox polygon
    std::vector<QPoint> mmb{v1,v2,v3,v4};

    //Calculate area minmaxbox
    area=(px_max.x()-px_min.x())*(py_max.y()-py_min.y());

    return {mmb, area};
}

QPolygon Algorithms::minAreaEnclosingRectangle(std::vector<QPoint> &points)
{
    //Creating min area enclosing rectangle
    QPolygon ch=cHull(points);

    //Searching for minmaxbox with min area
    int n = ch.size();
    double sigma_min=0;
    std::vector<QPoint> mmb_min;

    //Initializing min area
    auto[mmb, area_min]=minMaxBox(points);

    for (int i=0; i<n; i++)
    {
        //Calc coord diff
        double dx=ch[(i+1)%n].x()-ch[i].x();
        double dy=ch[(i+1)%n].y()-ch[i].y();

        double sigma = atan2(dy,dx);

        //Rotate by -sigma
        std::vector<QPoint>r_points = rotate(points, -sigma);

        //Create minmaxbox
        auto[mmb, area]=minMaxBox(r_points);

        //Searching for minimum

        if (area < area_min)
        {
           area_min=area;
           sigma_min=sigma;
           mmb_min=mmb;
        }
    }
    //Create enclosing rectangle
    std::vector<QPoint> er = rotate(mmb_min, sigma_min);

    //Convert to qpolygon
    QPolygon er_pol{er[0],er[1],er[2],er[3]};

    return er_pol;
}

#include "algorithms.h"
#include<cmath>

Algorithms::Algorithms()
{

}


double Algorithms::get2LinesAngle(QPoint &p1, QPoint &p2, QPoint &p3, QPoint &p4)
{
    //Comupute angle formed by two lines

    //Calculate coord diff
    double ux=p2.x()-p1.x();
    double uy=p2.y()-p1.y();

    double vx=p4.x()-p3.x();
    double vy=p4.y()-p3.y();

    //Dot product
    double dp=ux*vx+uy*vy;

    //Norms
    double nu=sqrt(ux*ux+uy*uy);
    double nv=sqrt(vx*vx+vy*vy);

    //Angle
    return fabs(acos(dp/(nu*nv)));


}

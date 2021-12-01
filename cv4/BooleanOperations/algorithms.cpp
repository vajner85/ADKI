#include "algorithms.h"

Algorithms::Algorithms()
{

}

TPointLinePosition Algorithms::getPointLinePosition(QPointFBO &a, QPointFBO &p1, QPointFBO &p2)
{
    double eps=1.0e-10;

    //Calculate coord diff
    double ux=p2.x()-p1.x();
    double uy=p2.y()-p1.y();

    double vx=a.x()-p1.x();
    double vy=a.y()-p1.y();

    //Halfplate test
    double t=ux*vy-vx*uy;

    //Point in the left half plane
    if (t>eps)
    {
     return LeftHP;
    }

    //Point in the right half plane
    if (t<-eps)
    {
     return RightHP;
    }

    //Point on the line
    return On;
}

double Algorithms::get2LinesAngle(QPointFBO &p1, QPointFBO &p2, QPointFBO &p3, QPointFBO &p4)
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

TPointPolygonPosition Algorithms::getPositionWinding(QPointFBO &q, TPolygon &pol)
{
    //Analyze position of point and polygon
    int n=pol.size();
    double omega_sum=0;

    //Process all segments of polygon
    for(int i=0; i<n;i++)
    {

        //Compute angle two line segments
        double omega=get2LinesAngle(pol[i],q,pol[(i+1)%n],q);

        //Compute position of point and line segment
        TPointLinePosition pos=getPointLinePosition(q,pol[i],pol[(i+1)%n]);

        //Point in the left halfplane
        if(pos==LeftHP)
            {omega_sum +=omega;}
        else if(pos==RightHP)
            {omega_sum -=omega;}
        else {return Boundary;}
    }

    //Point inside polygon
    double eps=1.0e-10;
    if (fabs(fabs(omega_sum)-2*M_PI) < eps)
        {return Inner;}
    else
        {return Outer;}

}

std::tuple<QPointFBO, T2LinePosition> get2LinesIntersection(QPointFBO &p1, QPointFBO &p2, QPointFBO &p3, QPointFBO &p4)
{
    //Get intersect 2 lines
    double ux=p2.x() - p1.x();
    double uy=p2.y() - p1.y();

    double vx = p4.x() - p3.x();
    double vy = p4.y() - p3.y();

    double wx=p1.x()-p3.x();


}

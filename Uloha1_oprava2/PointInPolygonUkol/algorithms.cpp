#include "algorithms.h"
#include <cmath>

Algorithms::Algorithms()
{

}

int Algorithms::getPointLinePosition(QPointF &a, QPointF &p1, QPointF &p2)
{
    double eps=1.0e-10;

    //Calculate coord diff
    double ux=p2.x()-p1.x();
    double uy=p2.y()-p1.y();

    double vx=a.x()-p1.x();
    double vy=a.y()-p1.y();

    //Halfplate test
    double t=ux*vy-vx*uy;

    //Singulairty test -- point a identical to p1/p2
    if ( ((a.x()==p1.x()) && (a.y()==p1.y())) || ((a.x()==p2.x()) && (a.y()==p2.y())) )
    {return -2;}

    //Point in the left half plane
    if (t>eps)
    {
     return 1;
    }

    //Point in the right half plane
    if (t<-eps)
    {
     return 0;
    }

    //Point on the line
    else return -1;
}

double Algorithms::get2LinesAngle(QPointF &p1, QPointF &p2, QPointF &p3, QPointF &p4)
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

int Algorithms::getPositionWinding(QPointF &q, std::vector<QPointF> &pol)
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
        int poss=getPointLinePosition(q,pol[i],pol[(i+1)%n]);

        //Point in the left halfplane
        if(poss==1)
            {omega_sum +=omega;}
        else if (poss==0)
            {omega_sum -=omega;}
        else {return -1;}
    }


    //Point inside polygon
    double eps=1.0e-10;
    if (fabs(fabs(omega_sum)-2*M_PI) < eps)
        {return 1;}
    else
        {return 0;}
}
int Algorithms::getPositionRayCrossing(QPointF &q, std::vector<QPointF> &pol)
{
    //Analyze position of point and polygon
    int n=pol.size();
    int eps=1.0e-10;

    //Intersection count
    int k=0;    //right
    int k1=0;   //left

    //Covering all vertices of a polygon
    for (int i=1; i<n+1;i++)
    {
        //Computing xc,yc,xcc,ycc
        double xc=pol[i%n].x()-q.x();
        double yc=pol[i%n].y()-q.y();

        double xcc=pol[i-1].x()-q.x();
        double ycc=pol[i-1].y()-q.y();

        //Finding intersection
        if ((yc>0) && (ycc<=0) || (ycc>0) && (yc<=0))
        {
            //Computing intersection
            double xcm=(xc*ycc-xcc*yc)/(yc-ycc);

            //Right/left plane
                if(xcm>-eps)
                    k = k+1;    //right
                if (xcm<eps)
                    k1 = k1+1;  //left
        }
    }

    //Border singularity
    if (k1%2<k%2 || k1%2>k%2)
        {return -1;}

    if ((k%2)!=0)
        {return 1;}
    else
        {return 0;}
}







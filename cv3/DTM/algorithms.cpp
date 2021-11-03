#include "algorithms.h"
#include <list>
#include "sortbyx.h"

Algorithms::Algorithms()
{

}

int Algorithms::getPointLinePosition(QPoint &a, QPoint &p1, QPoint &p2)
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
     return 1;
    }

    //Point in the right half plane
    if (t<-eps)
    {
     return 0;
    }

    //Point on the line
    return -1;
}

std::tuple<QPoint,double> Algorithms::getCircleCenterAndRadius(QPoint &p1,QPoint &p2,QPoint &p3)
{
    //Return center and radius of inscribed circle
    double k1= p1.x()*p1.x()+p1.y()*p1.y();
    double k2= p2.x()*p2.x()+p2.y()*p2.y();
    double k3= p3.x()*p3.x()+p3.y()*p3.y();

    double k4=p1.y()-p2.y();
    double k5=p1.y()-p3.y();
    double k6=p2.y()-p3.y();

    double k7=p1.x()-p2.x();
    double k8=p1.x()-p3.x();
    double k9=p2.x()-p3.x();

    double k10=p1.x()*p1.x();
    double k11=p2.x()*p2.x();
    double k12=p3.x()*p3.x();

    //Calculating centre of inscribed circle
    double m = 0.5*(-k12*k4+k11*k5-(k10+k4*k5)*k6)/(-p3.x()*k4+p2.x()*k5-p1.x()*k6);

    double n= 0.5*(-k1*k9+k2*k8-k3*k7)/(-p1.y()*k9+p2.y()*k8-p3.y()*k7);

    double r=sqrt(((p1.x()-m)*(p1.x()-m))+((p1.y()-n)*(p1.y()-n)));

    //Create center
    QPoint c(m,n);

    return{c,r};
}

int Algorithms::getDelaunayPoint(QPoint &s, QPoint &e, std::vector<QPoint> &points)
{
    //Find and return delaunay point
    int min_index =-1;
    double min_r = 1.e16;

    for(int i=0; i<points.size();i++)
    {
        //Point is different drom s,e
        if((points[i]!=s) && (points[i]!=e))
        {
            //Point in lefthalf plane
            if (getPointLinePosition(points[i],s,e)==1)
            {
                //Center and radius of inscribed circle
                auto[c,r]= getCircleCenterAndRadius(points[i],s,e);

                //Correct radius
                if (getPointLinePosition(c,s,e)==0)
                {r=-r;}

                //Updating minimum
                if(r<min_r)
                {
                    min_r=r;
                    min_index=i;
                }
            }
        }
    }
    return min_index;
}

int Algorithms::getNearestPoint(QPoint &p, std::vector<QPoint> &points)
{
    //Finding nearest point
    double min_dist= 1.e16;
    double min_ind = -1;

    for(int i=0; i<points.size(); i++)
    {
        if(points[i]!=p)
        {
            double dist = sqrt(((points[i].x()-p.x())*(points[i].x()-p.x()))+((points[i].y()-p.y())*(points[i].y()-p.y())));

            //Update minimum
            if(dist<min_dist)
            {
                min_dist=dist;
                min_ind=i;
            }
        }
    }
    return min_ind;
}

std::vector<Edge> Algorithms::dT(std::vector<QPoint> &points)
{
    //Creating Delaunay triangulation using incremental method
    std::vector<Edge> dt;
    std::list<Edge> ale;

    //Finding min x point ->pivot
    QPoint q= *min_element(points.begin(), points.end(),sortByX());

    //Point nearest to pivot q
    int i_nearest = getNearestPoint(q,points);
    QPoint qn= points[i_nearest];

}

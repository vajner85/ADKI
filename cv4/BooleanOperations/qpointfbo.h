#ifndef QPOINTFBO_H
#define QPOINTFBO_H

#include "Types.h"
#include <QtGui>

class QPointFBO : public QPointF
{

private:
    double alpha,beta;
    TPointPolygonPosition pos;

public:
    QPointFBO():alpha(0.0), beta(0.0), pos(Inner), QPointF(0,0){};
    QPointFBO(double alpha_, double beta_, TPointPolygonPosition pos_, float x_, float y_):alpha(alpha_), beta(beta_), pos(pos_), QPointF(x_,y_){};

    void setAlpha(double alpha_){alpha=alpha_;};
    void setBeta(double beta_){beta=beta_;};
    void setBeta(TPointPolygonPosition pos_){pos=pos_;};
    double getAlpha(){return alpha;};
    double getBeta(){return beta;};
    TPointPolygonPosition getPos(){return pos;};


};

#endif // QPOINTFBO_H

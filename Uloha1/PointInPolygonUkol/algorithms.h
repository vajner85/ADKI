#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QtGui>
#include <vector>

class Algorithms
{
public:
    Algorithms();
    int getPointLinePosition(QPointF &a, QPointF &p1, QPointF &p2);
    double get2LinesAngle(QPointF &p1, QPointF &p2, QPointF &p3, QPointF &p4);
    int getPositionWinding(QPointF &q, std::vector<QPointF> &pol);
    int getPositionRayCrossing(QPointF &q, std::vector<QPointF>&pol);

};

#endif // ALGORITHMS_H

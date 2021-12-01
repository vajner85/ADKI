#ifndef TYPES_H
#define TYPES_H
#include <QtGui>

#include "qpointfbo.h"
class QPointFBO;

//Position of point and line
typedef enum
{
    LeftHP,
    RightHP,
    On
} TPointLinePosition;

//Position of polygon and line
typedef enum
{
    Inner,
    Outer,
    Boundary
}TPointPolygonPosition;

//Boolean operation
typedef enum
{
    Union,
    Intersection,
    DifferenceA_B,
    DifferenceB_A,
}TBooleanOperation;

//Position of line and line
typedef enum
{
    Colinear,
    Parallel,
    Intersect,
    NonIntersect
} T2LinePosition;

//Polygon
typedef std::vector<QPointF>TPolygon;

#endif // TYPES_H

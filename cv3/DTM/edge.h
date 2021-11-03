#ifndef EDGE_H
#define EDGE_H

#include<QtGui>

class Edge
{
private:
    QPoint s,e;

public:
    Edge(QPoint &s_, QPoint &e_):s(s_),e(e_){};
    void changeOrientation(){QPoint temp=s; s=e; e=temp;};




};

#endif // EDGE_H

#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include "qpoint3d.h"
#include <QtGui>
#include "edge.h"
#include "triangle.h"


class Draw : public QWidget
{
    Q_OBJECT
private:
    std::vector<QPoint3D> points;
    std::vector<Edge> dt;
    std::vector<Edge> contours;
    std::vector<Triangle> triangles;
    std::vector<Edge> contourslabel,contourslabel2, contoursmain;
    boolean greycol, colors;
    int width,height;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void clear();
    std::vector<QPoint3D> getPoints(){return points;}
    void setDT(std::vector<Edge> &dt_){dt = dt_;}
    std::vector<Edge> getDT(){return dt;};
    void setContours(std::vector<Edge> &contours_){contours = contours_;}
    std::vector<Edge> geContours(){return contours;};
    std::vector<Triangle> getTriangles(){return triangles;};
    void setTriangle(std::vector<Triangle> &triangles_){triangles = triangles_;};
    void clearDT();

    void setLabelContours(std::vector<Edge> &contourslabel_){contourslabel = contourslabel_;}
    std::vector<Edge>& getLabelContours() {return contourslabel;}
    void setMainContours(std::vector<Edge> &contoursmain_){contoursmain = contoursmain_;}
    std::vector<Edge>& getMainContours() {return contoursmain;}

    void setGreycol(bool &greycol_){greycol = greycol_;};
    void setColors(bool &colors_){colors = colors_;};

    void loadFile(std::string &path);

    int getWidth(){return width;}
    int getHeight(){return height;}

    void setWidth(int width_){width=width_;};
    void setHeight(int height_){height=height_;};


signals:

public slots:
};

#endif // DRAW_H

#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <QtGui>

class Draw : public QWidget
{
    Q_OBJECT
private:
    std::vector<QPoint> points;
    QPolygon ch, er;
    std::vector<QPolygon> ch_v, er_v;
    std::vector<QPolygon> pol;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void clear();
    std::vector<QPoint> getPoints(){return points;}
    void setCh(QPolygon &ch_){ch = ch_;}
    void setEr(QPolygon &er_){er = er_;}
    void loadFile(std::string &path);

    std::vector<QPolygon> getPolygon(){return pol;};
    void addCh(QPolygon &ch_){ch_v.push_back(ch_);}
    void addEr(QPolygon &er_){er_v.push_back(er_);}

signals:

public slots:
};

#endif // DRAW_H

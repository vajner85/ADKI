#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include "edge.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_2_clicked()
{
    ui->Canvas->clear();
    repaint();
}


void Widget::on_pushButton_clicked()
{
    //Get points
    std::vector<QPoint> points=ui->Canvas->getPoints();

    //Create dt
    Algorithms a;
    std::vector<Edge> dt=a.dT(points);

    ui->Canvas->setDT(dt);

    repaint();
}


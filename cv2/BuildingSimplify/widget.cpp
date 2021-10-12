#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"


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
    ui->canvas->clear();
}


void Widget::on_pushButton_clicked()
{
    std::vector<QPoint> points = ui->canvas->getPoints();
    Algorithms a;
    QPolygon ch=a.cHull(points);
    ui->canvas->setCh(ch);
    repaint();

}


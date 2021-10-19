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
    ui->Canvas->clear();
}

void Widget::on_pushButton_clicked()
{
    //Get points
    std::vector<QPoint> points = ui->Canvas->getPoints();

    //Create enclosing rectangle
    Algorithms a;
    QPolygon ch = a.cHull(points);
    QPolygon er = a.minAreaEnclosingRectangle(points);

    //Update enclosing rectangle
    ui->Canvas->setEr(er);
    ui->Canvas->setCh(ch);
    //Repaint
    repaint();

}

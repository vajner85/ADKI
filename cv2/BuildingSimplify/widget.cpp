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
     QPolygon er;
    //Create enclosing rectangle
    Algorithms a;
    QPolygon ch = a.cHull(points);
    if (ui->comboBox->currentIndex()==0)
        {er = a.minAreaEnclosingRectangle(points);
        ui->Canvas->setCh(ch);
        }
    if (ui->comboBox->currentIndex()==1)
        {er = a.wallAverage(points);}

    //Update enclosing rectangle
    ui->Canvas->setEr(er);

    //Repaint
    repaint();

}

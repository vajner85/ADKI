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
    QPolygon er;
    if (ui->comboBox->currentIndex()==0)
        {   er = a.minAreaEnclosingRectangle(points);
        QPolygon ch = a.cHull(points);
        ui->Canvas->setCh(ch); }

     if (ui->comboBox->currentIndex()==1)
        {er = a.wallAverage(points);}

     if (ui->comboBox->currentIndex()==2)
        {er = a.longestEdge(points);}

     if (ui->comboBox->currentIndex()==3)
        {er = a.weightedBisector(points);}


    //Update enclosing rectangle
    ui->Canvas->setEr(er);

    //Repaint
    repaint();
}

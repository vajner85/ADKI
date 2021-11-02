#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include <QFileDialog>

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

void Widget::on_pushButtonLoadFile_clicked()
{   //Load function
    QString path(QFileDialog::getOpenFileName
                 (this, tr("Opening of file"),
                  "../",
                  tr("Text Files (*.txt)")));
       std::string path_ = path.toStdString();

       ui->Canvas->loadFile(path_);
}

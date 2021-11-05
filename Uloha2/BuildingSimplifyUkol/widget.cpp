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
    //std::vector<QPoint> points = ui->Canvas->getPoints();
    std::vector<QPolygon> pol=ui->Canvas->getPolygon();

    std::vector<QPoint> point;
    std::vector<QPoint> points;
    //Create enclosing rectangle
    Algorithms a;
    QPolygon er;
    std::vector<QPolygon> ch_v, er_v;
    QPolygon polygon;

    for (unsigned int i=0; i<pol.size(); i++)
        {
            polygon.clear();
            polygon.append(pol[i]);
            points.clear();

            for (unsigned int  j= 0; j< polygon.size(); j++)
                     {
                    points.push_back(polygon[j]);
                    }

        if (points.size() > 2)
        {
    if (ui->comboBox->currentIndex()==0)
        {   er = a.minAreaEnclosingRectangle(points);
        QPolygon ch = a.cHull(points);
        ui->Canvas->addCh(ch);
        }

     if (ui->comboBox->currentIndex()==1)
        {er = a.wallAverage(points);}

     if (ui->comboBox->currentIndex()==2)
        {er = a.longestEdge(points);}

     if (ui->comboBox->currentIndex()==3)
        {er = a.weightedBisector(points);}


    //Update enclosing rectangle
    ui->Canvas->addEr(er);

    //Repaint
    repaint();
        }
    }

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

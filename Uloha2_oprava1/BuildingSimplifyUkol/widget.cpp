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
    //Get polygons
    std::vector<QPolygon> pols=ui->Canvas->getPolygons();

    //Create enclosing rectangle
    Algorithms a;
    QPolygon er;
    std::vector<QPolygon> ch_v, er_v;
    QPolygon polygon;

    //Process polygons one by one
    for (unsigned int i=0; i<pols.size(); i++)
    {
        //Convert polygon to vector of points
        std::vector<QPoint> points;
        for (QPoint p : pols[i])
            points.push_back(p);

        if (points.size() > 2)
        {
            //Method-area enclosing rectangle
            if (ui->comboBox->currentIndex()==0)
            {
                er = a.minAreaEnclosingRectangle(points);
                QPolygon ch = a.cHull(points);
                ui->Canvas->addCh(ch);
            }

            //Method-wall average
            else if (ui->comboBox->currentIndex()==1)
                er = a.wallAverage(points);

            //Method-longest edge
            else if (ui->comboBox->currentIndex()==2)
               er = a.longestEdge(points);

            //Method-weighted bisector
            else if (ui->comboBox->currentIndex()==3)
               er = a.weightedBisector(points);
        }

        //Update enclosing rectangle
        ui->Canvas->addEr(er);

        //Repaint
        repaint();
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

#include "widget.h"
#include "ui_widget.h"
#include <algorithms.h>
#include <fstream>
#include <fstream>
#include "draw.h"
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


void Widget::on_pushButtonClear_clicked()
{
    ui->Canvas->clear();
}

void Widget::on_pushButton_clicked()
{
    ui->Canvas->changeStatus();
}


void Widget::on_pushButtonAnalyze_clicked()
{
    //Analyze point & polygon position
    QPointF q=ui->Canvas->getPoint();
    std::vector<QPolygonF> pol=ui->Canvas->getPolygon();
    Algorithms a;
    int pos =-3;
    std::vector<QPointF> poly;

    for (int i=0; i<pol.size(); i++)
    {
        QPolygonF polygon = pol[i];

        for (int  j= 0; j< polygon.size(); j++)
             {


            poly.push_back(polygon[j]);

             }

        if (ui->methodcomboBox->currentIndex()==0)
            {pos=a.getPositionWinding(q,poly);}
        if (ui->methodcomboBox->currentIndex()==1)
            {pos=a.getPositionRayCrossing(q,poly);}

        //draw results
        if(pos==1)
            ui->label->setText("Inside");
        else if(pos==0)
            ui->label->setText("Outside");
        else if (pos==0)
            ui->label->setText("Border");
        else
            ui->label->setText("No data");
    }
}




void Widget::on_pushButtonLoadFile_clicked()
{
    QString path(QFileDialog::getOpenFileName
                 (this, tr("Opening of file"),
                  "../",
                  tr("Text Files (*.txt)")));
       std::string path_ = path.toStdString();

       ui->Canvas->loadFile(path_);
}


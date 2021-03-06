#include "widget.h"
#include "ui_widget.h"
#include <algorithms.h>


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
    QPoint q=ui->Canvas->getPoint();
    std::vector<QPoint> pol=ui->Canvas->getPolygon();
    Algorithms a;
    int pos =0;
    if (ui->methodcomboBox->currentIndex()==0)
        {pos=a.getPositionWinding(q,pol);}
    if (ui->methodcomboBox->currentIndex()==1)
        {pos=a.getPositionRayCrossing(q,pol);}

    //draw results
    if(pos==1)
        ui->label->setText("Inside");
    else if(pos==0)
        ui->label->setText("Outside");
    else
        ui->label->setText("Border");
}




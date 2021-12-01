#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include "edge.h"
#include <QFileDialog>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    zmin = 100.0;
    zmax = 1000.0;
    dz = 5.0;

    ui->lineEdit->setText(QString::number(zmin));
    ui->lineEdit_2->setText(QString::number(zmax));
    ui->lineEdit_3->setText(QString::number(dz));


    int width= ui->Canvas->getWidth();
    int height= ui->Canvas->getHeight();

    ui->Canvas->setHeight(height);
    ui->Canvas->setWidth(width);

}


Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_2_clicked()
{
    //Clear all
    ui->Canvas->clear();
    repaint();
}

void Widget::on_pushButton_clicked()
{
    //Get points
    std::vector<QPoint3D> points = ui->Canvas->getPoints();

    //Create DT
    Algorithms a;
    std::vector<Edge> dt = a.dT(points);

    //Set DT
    ui->Canvas->setDT(dt);

    repaint();

}

void Widget::on_pushButton_cleardt_clicked()
{
    //Clear DT
    ui->Canvas->clearDT();
    repaint();
}

void Widget::on_lineEdit_editingFinished()
{
    zmin = ui->lineEdit->text().toDouble();
}

void Widget::on_lineEdit_2_editingFinished()
{
    zmax = ui->lineEdit_2->text().toDouble();
}

void Widget::on_lineEdit_3_editingFinished()
{
    dz = ui->lineEdit_3->text().toDouble();
}

void Widget::on_pushButton_3_clicked()
{
    //Create contours
    std::vector<Edge> dt = ui->Canvas->getDT();

    //Is triangulation empty
    if(dt.size() > 0)
    {
        //Create contours
        Algorithms a;
        std::vector<Edge> contours = a.getContourLines(dt, zmin, zmax, dz);

        //Set contours
        ui->Canvas->setContours(contours);

        //Create main contours
        std::vector<Edge> contoursmain = a.getContourLines(dt, zmin, zmax, dz*5);

        //Set main contours
        ui->Canvas->setMainContours(contoursmain);

        //Get labels
        std::vector<Edge> &labels = ui->Canvas->getLabelContours();
        repaint();
    }
}


void Widget::on_pushButton_DrawSlope_clicked()
{
    //Create contours
    std::vector<Edge> dt = ui->Canvas->getDT();

    //Is triangulation empty
    if(dt.size() > 0)
    {
        //Analyze DTM
        Algorithms a;
        std::vector<Triangle> triangles = a.analyzeDTM(dt);

        //Set triangles
        ui->Canvas->setTriangle(triangles);

        repaint();
    }

    bool greycol = TRUE;
    bool colors = FALSE;

    if(ui->comboBoxCol->currentIndex()==0)
        {   greycol = TRUE;
            colors = FALSE;
        }

    if(ui->comboBoxCol->currentIndex()==1)
        {   greycol = FALSE;
            colors = TRUE;
        }

    ui->Canvas->setColors(colors);
    ui->Canvas->setGreycol(greycol);
}

void Widget::on_pushButton_labelsC_clicked()
{
    std::vector<Edge> contourslabel = ui -> Canvas -> getMainContours();

        ui->Canvas->setLabelContours(contourslabel);
        repaint();

}

void Widget::on_pushButtonLoadF_clicked()
{   //Load function
    QString path(QFileDialog::getOpenFileName
                 (this, tr("Opening of file"),
                  "../",
                  tr("Text Files (*.txt)")));
       std::string path_ = path.toStdString();

       ui->Canvas->loadFile(path_);

}

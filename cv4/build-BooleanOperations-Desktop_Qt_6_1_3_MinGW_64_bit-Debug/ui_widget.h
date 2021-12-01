/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <draw.h>

QT_BEGIN_NAMESPACE

class Ui_QWidget
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    Draw *Canvas;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QComboBox *comboBoxOperation;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButtonOverlay;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonClear;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *QWidget)
    {
        if (QWidget->objectName().isEmpty())
            QWidget->setObjectName(QString::fromUtf8("QWidget"));
        QWidget->resize(1023, 654);
        widget = new QWidget(QWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(2, 10, 1021, 641));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Canvas = new Draw(widget);
        Canvas->setObjectName(QString::fromUtf8("Canvas"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(Canvas->sizePolicy().hasHeightForWidth());
        Canvas->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(Canvas);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        comboBoxOperation = new QComboBox(widget);
        comboBoxOperation->addItem(QString());
        comboBoxOperation->addItem(QString());
        comboBoxOperation->addItem(QString());
        comboBoxOperation->addItem(QString());
        comboBoxOperation->setObjectName(QString::fromUtf8("comboBoxOperation"));

        verticalLayout->addWidget(comboBoxOperation);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        pushButtonOverlay = new QPushButton(widget);
        pushButtonOverlay->setObjectName(QString::fromUtf8("pushButtonOverlay"));

        verticalLayout->addWidget(pushButtonOverlay);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButtonClear = new QPushButton(widget);
        pushButtonClear->setObjectName(QString::fromUtf8("pushButtonClear"));

        verticalLayout->addWidget(pushButtonClear);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QWidget);

        QMetaObject::connectSlotsByName(QWidget);
    } // setupUi

    void retranslateUi(QWidget *QWidget)
    {
        QWidget->setWindowTitle(QCoreApplication::translate("QWidget", "BooleanOperationsPolygon", nullptr));
        pushButton->setText(QCoreApplication::translate("QWidget", "Switch A/B", nullptr));
        label->setText(QCoreApplication::translate("QWidget", "Boolean operation:", nullptr));
        comboBoxOperation->setItemText(0, QCoreApplication::translate("QWidget", "Union", nullptr));
        comboBoxOperation->setItemText(1, QCoreApplication::translate("QWidget", "Intersect", nullptr));
        comboBoxOperation->setItemText(2, QCoreApplication::translate("QWidget", "Difference A-B", nullptr));
        comboBoxOperation->setItemText(3, QCoreApplication::translate("QWidget", "Difference B-A", nullptr));

        pushButtonOverlay->setText(QCoreApplication::translate("QWidget", "Create overlay", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("QWidget", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QWidget: public Ui_QWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

/********************************************************************************
** Form generated from reading UI file 'CD_Cali.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CD_Cali_H
#define UI_CD_Cali_H

#include <QLineFreqEdit.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_CD_Cali
{
public:
    QGridLayout *gridLayout;
    QLineFreqEdit *lineFreqEdit;
    QLabel *label;
    QPushButton *startPushButton;
    QCustomPlot *plot;

    void setupUi(QDialog *CD_Cali)
    {
        if (CD_Cali->objectName().isEmpty())
            CD_Cali->setObjectName(QStringLiteral("CD_Cali"));
        CD_Cali->resize(274, 246);
        gridLayout = new QGridLayout(CD_Cali);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineFreqEdit = new QLineFreqEdit(CD_Cali);
        lineFreqEdit->setObjectName(QStringLiteral("lineFreqEdit"));

        gridLayout->addWidget(lineFreqEdit, 0, 1, 1, 1);

        label = new QLabel(CD_Cali);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        startPushButton = new QPushButton(CD_Cali);
        startPushButton->setObjectName(QStringLiteral("startPushButton"));

        gridLayout->addWidget(startPushButton, 0, 2, 1, 1);

        plot = new QCustomPlot(CD_Cali);
        plot->setObjectName(QStringLiteral("plot"));

        gridLayout->addWidget(plot, 1, 0, 1, 3);


        retranslateUi(CD_Cali);

        QMetaObject::connectSlotsByName(CD_Cali);
    } // setupUi

    void retranslateUi(QDialog *CD_Cali)
    {
        CD_Cali->setWindowTitle(QApplication::translate("CD_Cali", "Dialog", 0));
        label->setText(QApplication::translate("CD_Cali", "\351\242\221\347\202\271", 0));
        startPushButton->setText(QApplication::translate("CD_Cali", "\345\274\200\345\247\213", 0));
    } // retranslateUi

};

namespace Ui {
    class CD_Cali: public Ui_CD_Cali {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CD_Cali_H

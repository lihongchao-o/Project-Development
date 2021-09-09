/********************************************************************************
** Form generated from reading UI file 'CD_TxTable.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CD_TXTABLE_H
#define UI_CD_TXTABLE_H

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

class Ui_CD_TxTable
{
public:
    QGridLayout *gridLayout;
    QLineFreqEdit *lineFreqEdit;
    QLabel *label;
    QPushButton *startPushButton;
    QCustomPlot *plot;

    void setupUi(QDialog *CD_TxTable)
    {
        if (CD_TxTable->objectName().isEmpty())
            CD_TxTable->setObjectName(QStringLiteral("CD_TxTable"));
        CD_TxTable->resize(274, 246);
        gridLayout = new QGridLayout(CD_TxTable);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineFreqEdit = new QLineFreqEdit(CD_TxTable);
        lineFreqEdit->setObjectName(QStringLiteral("lineFreqEdit"));

        gridLayout->addWidget(lineFreqEdit, 0, 1, 1, 1);

        label = new QLabel(CD_TxTable);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        startPushButton = new QPushButton(CD_TxTable);
        startPushButton->setObjectName(QStringLiteral("startPushButton"));

        gridLayout->addWidget(startPushButton, 0, 2, 1, 1);

        plot = new QCustomPlot(CD_TxTable);
        plot->setObjectName(QStringLiteral("plot"));

        gridLayout->addWidget(plot, 1, 0, 1, 3);


        retranslateUi(CD_TxTable);

        QMetaObject::connectSlotsByName(CD_TxTable);
    } // setupUi

    void retranslateUi(QDialog *CD_TxTable)
    {
        CD_TxTable->setWindowTitle(QApplication::translate("CD_TxTable", "Dialog", 0));
        label->setText(QApplication::translate("CD_TxTable", "\351\242\221\347\202\271", 0));
        startPushButton->setText(QApplication::translate("CD_TxTable", "\345\274\200\345\247\213", 0));
    } // retranslateUi

};

namespace Ui {
    class CD_TxTable: public Ui_CD_TxTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CD_TXTABLE_H

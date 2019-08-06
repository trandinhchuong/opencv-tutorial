/********************************************************************************
** Form generated from reading UI file 'facedetect.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEDETECT_H
#define UI_FACEDETECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_facedetect
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *facedetect)
    {
        if (facedetect->objectName().isEmpty())
            facedetect->setObjectName(QStringLiteral("facedetect"));
        facedetect->resize(400, 300);
        menuBar = new QMenuBar(facedetect);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        facedetect->setMenuBar(menuBar);
        mainToolBar = new QToolBar(facedetect);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        facedetect->addToolBar(mainToolBar);
        centralWidget = new QWidget(facedetect);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        facedetect->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(facedetect);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        facedetect->setStatusBar(statusBar);

        retranslateUi(facedetect);

        QMetaObject::connectSlotsByName(facedetect);
    } // setupUi

    void retranslateUi(QMainWindow *facedetect)
    {
        facedetect->setWindowTitle(QApplication::translate("facedetect", "facedetect", 0));
    } // retranslateUi

};

namespace Ui {
    class facedetect: public Ui_facedetect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEDETECT_H

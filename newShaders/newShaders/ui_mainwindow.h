/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <glwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    GLWidget *widget;
    QGroupBox *groupBox;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QRadioButton *render_Phong;
    QRadioButton *render_Gooch;
    QRadioButton *render_ShadowMap;
    QCheckBox *showNormalButton;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(528, 299);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new GLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 341, 281));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(370, 10, 141, 150));
        widget1 = new QWidget(groupBox);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(10, 30, 119, 80));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        render_Phong = new QRadioButton(widget1);
        render_Phong->setObjectName(QStringLiteral("render_Phong"));
        render_Phong->setChecked(true);

        verticalLayout->addWidget(render_Phong);

        render_Gooch = new QRadioButton(widget1);
        render_Gooch->setObjectName(QStringLiteral("render_Gooch"));

        verticalLayout->addWidget(render_Gooch);

        render_ShadowMap = new QRadioButton(widget1);
        render_ShadowMap->setObjectName(QStringLiteral("render_ShadowMap"));

        verticalLayout->addWidget(render_ShadowMap);

        showNormalButton = new QCheckBox(groupBox);
        showNormalButton->setObjectName(QStringLiteral("showNormalButton"));
        showNormalButton->setGeometry(QRect(10, 130, 121, 22));
        showNormalButton->setChecked(false);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(360, 260, 161, 27));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Render", 0));
        render_Phong->setText(QApplication::translate("MainWindow", "Phong", 0));
        render_Gooch->setText(QApplication::translate("MainWindow", "Gooch", 0));
        render_ShadowMap->setText(QApplication::translate("MainWindow", "Shadow Map", 0));
        showNormalButton->setText(QApplication::translate("MainWindow", "show normals", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Reload Shader", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

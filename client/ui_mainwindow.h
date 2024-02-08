/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_register;
    QLineEdit *lineEdit_login;
    QPushButton *pushButton_backtologin;
    QPushButton *pushButton_backtoregister;
    QPushButton *pushButton_login;
    QLineEdit *lineEdit_password;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit_registerIp;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(912, 593);
        MainWindow->setStyleSheet(QString::fromUtf8("*\n"
"{\n"
"background-color: rgb(54, 57, 62);\n"
"color:white;\n"
"font-family: Verdana, Geneva, sans-serif;\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"border-radius: 15px;\n"
"padding:10px;\n"
"border:2px solid #FC1C14;\n"
"margin-left:100%;\n"
"margin-right:100%;\n"
"color:white\n"
"}\n"
"\n"
"\n"
"QPushButton\n"
"{\n"
"border:2px solid #FC1C14;\n"
"border-radius: 15px;\n"
"color:white;\n"
"margin-left:100%;\n"
"margin-right:100%;\n"
"padding:10%;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background-color:#FC1C14;\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QMessageBox\n"
"{\n"
"background-color: rgb(54, 57, 62);\n"
"color:white;\n"
"font-family: Verdana, Geneva, sans-serif;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 10, 0, 1, 1);

        pushButton_register = new QPushButton(centralwidget);
        pushButton_register->setObjectName(QString::fromUtf8("pushButton_register"));
        pushButton_register->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(pushButton_register, 7, 0, 1, 1);

        lineEdit_login = new QLineEdit(centralwidget);
        lineEdit_login->setObjectName(QString::fromUtf8("lineEdit_login"));

        gridLayout->addWidget(lineEdit_login, 2, 0, 1, 1);

        pushButton_backtologin = new QPushButton(centralwidget);
        pushButton_backtologin->setObjectName(QString::fromUtf8("pushButton_backtologin"));
        pushButton_backtologin->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(pushButton_backtologin, 8, 0, 1, 1);

        pushButton_backtoregister = new QPushButton(centralwidget);
        pushButton_backtoregister->setObjectName(QString::fromUtf8("pushButton_backtoregister"));
        pushButton_backtoregister->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(pushButton_backtoregister, 9, 0, 1, 1);

        pushButton_login = new QPushButton(centralwidget);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(pushButton_login, 6, 0, 1, 1);

        lineEdit_password = new QLineEdit(centralwidget);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_password, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        lineEdit_registerIp = new QLineEdit(centralwidget);
        lineEdit_registerIp->setObjectName(QString::fromUtf8("lineEdit_registerIp"));

        gridLayout->addWidget(lineEdit_registerIp, 4, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_register->setText(QCoreApplication::translate("MainWindow", "Register", nullptr));
        lineEdit_login->setInputMask(QString());
        lineEdit_login->setText(QString());
        lineEdit_login->setPlaceholderText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        pushButton_backtologin->setText(QCoreApplication::translate("MainWindow", "Back to Login", nullptr));
        pushButton_backtoregister->setText(QCoreApplication::translate("MainWindow", "Create Account", nullptr));
        pushButton_login->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        lineEdit_password->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        lineEdit_registerIp->setPlaceholderText(QCoreApplication::translate("MainWindow", "IP Address", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:72pt; font-weight:700; color:#fc1c14;\">MATI</span><span style=\" font-size:72pt; font-weight:700; color:white;\">MAX</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

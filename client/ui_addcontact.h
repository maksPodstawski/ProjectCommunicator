/********************************************************************************
** Form generated from reading UI file 'addcontact.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCONTACT_H
#define UI_ADDCONTACT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_AddContact
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_contactIP;
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit_ContactName;

    void setupUi(QDialog *AddContact)
    {
        if (AddContact->objectName().isEmpty())
            AddContact->setObjectName(QString::fromUtf8("AddContact"));
        AddContact->resize(275, 198);
        AddContact->setMinimumSize(QSize(275, 198));
        AddContact->setStyleSheet(QString::fromUtf8("*\n"
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
"color:white\n"
"}\n"
"\n"
"\n"
"QPushButton\n"
"{\n"
"border:2px solid #FC1C14;\n"
"border-radius: 15px;\n"
"color:white;\n"
"padding:10%;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"background-color:#FC1C14;\n"
"font-weight: bold;\n"
"}\n"
""));
        gridLayout_2 = new QGridLayout(AddContact);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit_contactIP = new QLineEdit(AddContact);
        lineEdit_contactIP->setObjectName(QString::fromUtf8("lineEdit_contactIP"));

        gridLayout->addWidget(lineEdit_contactIP, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(AddContact);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setCursor(QCursor(Qt::PointingHandCursor));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

        lineEdit_ContactName = new QLineEdit(AddContact);
        lineEdit_ContactName->setObjectName(QString::fromUtf8("lineEdit_ContactName"));

        gridLayout->addWidget(lineEdit_ContactName, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(AddContact);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, AddContact, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AddContact, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(AddContact);
    } // setupUi

    void retranslateUi(QDialog *AddContact)
    {
        AddContact->setWindowTitle(QCoreApplication::translate("AddContact", "Dialog", nullptr));
        lineEdit_contactIP->setPlaceholderText(QCoreApplication::translate("AddContact", "Contact IP", nullptr));
        lineEdit_ContactName->setPlaceholderText(QCoreApplication::translate("AddContact", "Contact Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddContact: public Ui_AddContact {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCONTACT_H

/********************************************************************************
** Form generated from reading UI file 'addgroup.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDGROUP_H
#define UI_ADDGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_addGroup
{
public:
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_groupName;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *addGroup)
    {
        if (addGroup->objectName().isEmpty())
            addGroup->setObjectName(QString::fromUtf8("addGroup"));
        addGroup->resize(279, 121);
        addGroup->setStyleSheet(QString::fromUtf8("*\n"
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
        formLayout = new QFormLayout(addGroup);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEdit_groupName = new QLineEdit(addGroup);
        lineEdit_groupName->setObjectName(QString::fromUtf8("lineEdit_groupName"));

        verticalLayout->addWidget(lineEdit_groupName);

        buttonBox = new QDialogButtonBox(addGroup);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        formLayout->setLayout(0, QFormLayout::SpanningRole, verticalLayout);


        retranslateUi(addGroup);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, addGroup, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, addGroup, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(addGroup);
    } // setupUi

    void retranslateUi(QDialog *addGroup)
    {
        addGroup->setWindowTitle(QCoreApplication::translate("addGroup", "Dialog", nullptr));
        lineEdit_groupName->setPlaceholderText(QCoreApplication::translate("addGroup", "Group name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addGroup: public Ui_addGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDGROUP_H

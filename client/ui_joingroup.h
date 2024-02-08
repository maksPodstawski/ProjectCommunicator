/********************************************************************************
** Form generated from reading UI file 'joingroup.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINGROUP_H
#define UI_JOINGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_joinGroup
{
public:
    QFormLayout *formLayout_2;
    QFormLayout *formLayout;
    QLineEdit *lineEdit_groupCode;
    QLineEdit *lineEdit_groupName;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *joinGroup)
    {
        if (joinGroup->objectName().isEmpty())
            joinGroup->setObjectName(QString::fromUtf8("joinGroup"));
        joinGroup->resize(288, 153);
        joinGroup->setStyleSheet(QString::fromUtf8("*\n"
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
        formLayout_2 = new QFormLayout(joinGroup);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        lineEdit_groupCode = new QLineEdit(joinGroup);
        lineEdit_groupCode->setObjectName(QString::fromUtf8("lineEdit_groupCode"));

        formLayout->setWidget(1, QFormLayout::SpanningRole, lineEdit_groupCode);

        lineEdit_groupName = new QLineEdit(joinGroup);
        lineEdit_groupName->setObjectName(QString::fromUtf8("lineEdit_groupName"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, lineEdit_groupName);

        buttonBox = new QDialogButtonBox(joinGroup);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(2, QFormLayout::SpanningRole, buttonBox);


        formLayout_2->setLayout(0, QFormLayout::SpanningRole, formLayout);


        retranslateUi(joinGroup);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, joinGroup, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, joinGroup, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(joinGroup);
    } // setupUi

    void retranslateUi(QDialog *joinGroup)
    {
        joinGroup->setWindowTitle(QCoreApplication::translate("joinGroup", "Dialog", nullptr));
        lineEdit_groupCode->setPlaceholderText(QCoreApplication::translate("joinGroup", "Group Code", nullptr));
        lineEdit_groupName->setPlaceholderText(QCoreApplication::translate("joinGroup", "Group Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class joinGroup: public Ui_joinGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINGROUP_H

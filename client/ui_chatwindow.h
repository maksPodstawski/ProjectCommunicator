/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QListWidget *listWidget_messages;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_message;
    QPushButton *pushButton_sendMessage;
    QSplitter *splitter;
    QListWidget *listWidget_contacts;
    QListWidget *listWidget_Groups;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_profileContact;
    QLabel *label_ContactName;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_UserName;
    QLabel *label_profileUser;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_logout;
    QPushButton *pushButton_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_privateChats;
    QPushButton *pushButton_groupChats;
    QPushButton *pushButton_joinGroupChat;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_AddGroupChat;
    QPushButton *pushButton;

    void setupUi(QMainWindow *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName(QString::fromUtf8("ChatWindow"));
        ChatWindow->resize(976, 546);
        ChatWindow->setStyleSheet(QString::fromUtf8("*\n"
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
"\n"
"QPushButton:disabled\n"
"{\n"
"border-color:gray;\n"
"}\n"
"\n"
"QListWidget:item:hover{background-color:#525252;}\n"
"\n"
"QListWidget:item:selected{background-color:#525252; color:white; border:1px dotted white;}"));
        centralwidget = new QWidget(ChatWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        listWidget_messages = new QListWidget(centralwidget);
        listWidget_messages->setObjectName(QString::fromUtf8("listWidget_messages"));

        verticalLayout_4->addWidget(listWidget_messages);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit_message = new QLineEdit(centralwidget);
        lineEdit_message->setObjectName(QString::fromUtf8("lineEdit_message"));

        horizontalLayout_2->addWidget(lineEdit_message);

        pushButton_sendMessage = new QPushButton(centralwidget);
        pushButton_sendMessage->setObjectName(QString::fromUtf8("pushButton_sendMessage"));
        pushButton_sendMessage->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(pushButton_sendMessage);


        verticalLayout_4->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_4, 1, 1, 2, 1);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        listWidget_contacts = new QListWidget(splitter);
        listWidget_contacts->setObjectName(QString::fromUtf8("listWidget_contacts"));
        splitter->addWidget(listWidget_contacts);
        listWidget_Groups = new QListWidget(splitter);
        listWidget_Groups->setObjectName(QString::fromUtf8("listWidget_Groups"));
        splitter->addWidget(listWidget_Groups);

        gridLayout->addWidget(splitter, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_profileContact = new QLabel(centralwidget);
        label_profileContact->setObjectName(QString::fromUtf8("label_profileContact"));
        label_profileContact->setMinimumSize(QSize(128, 128));

        horizontalLayout_3->addWidget(label_profileContact);

        label_ContactName = new QLabel(centralwidget);
        label_ContactName->setObjectName(QString::fromUtf8("label_ContactName"));

        horizontalLayout_3->addWidget(label_ContactName);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        label_UserName = new QLabel(centralwidget);
        label_UserName->setObjectName(QString::fromUtf8("label_UserName"));

        horizontalLayout_3->addWidget(label_UserName);

        label_profileUser = new QLabel(centralwidget);
        label_profileUser->setObjectName(QString::fromUtf8("label_profileUser"));
        label_profileUser->setMinimumSize(QSize(128, 128));

        horizontalLayout_3->addWidget(label_profileUser);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pushButton_logout = new QPushButton(centralwidget);
        pushButton_logout->setObjectName(QString::fromUtf8("pushButton_logout"));
        pushButton_logout->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_3->addWidget(pushButton_logout);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_3->addWidget(pushButton_2);


        horizontalLayout_4->addLayout(verticalLayout_3);


        gridLayout->addLayout(horizontalLayout_4, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_privateChats = new QPushButton(centralwidget);
        pushButton_privateChats->setObjectName(QString::fromUtf8("pushButton_privateChats"));
        pushButton_privateChats->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(pushButton_privateChats);

        pushButton_groupChats = new QPushButton(centralwidget);
        pushButton_groupChats->setObjectName(QString::fromUtf8("pushButton_groupChats"));
        pushButton_groupChats->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(pushButton_groupChats);


        verticalLayout->addLayout(horizontalLayout);

        pushButton_joinGroupChat = new QPushButton(centralwidget);
        pushButton_joinGroupChat->setObjectName(QString::fromUtf8("pushButton_joinGroupChat"));
        pushButton_joinGroupChat->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(pushButton_joinGroupChat);


        gridLayout->addLayout(verticalLayout, 2, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_AddGroupChat = new QPushButton(centralwidget);
        pushButton_AddGroupChat->setObjectName(QString::fromUtf8("pushButton_AddGroupChat"));
        pushButton_AddGroupChat->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_2->addWidget(pushButton_AddGroupChat);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_2->addWidget(pushButton);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        ChatWindow->setCentralWidget(centralwidget);

        retranslateUi(ChatWindow);

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "MainWindow", nullptr));
        pushButton_sendMessage->setText(QCoreApplication::translate("ChatWindow", "Send", nullptr));
        label_profileContact->setText(QString());
        label_ContactName->setText(QString());
        label_UserName->setText(QString());
        label_profileUser->setText(QString());
        pushButton_logout->setText(QCoreApplication::translate("ChatWindow", "Logout", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ChatWindow", "Avatar", nullptr));
        pushButton_privateChats->setText(QCoreApplication::translate("ChatWindow", "Private Chats", nullptr));
        pushButton_groupChats->setText(QCoreApplication::translate("ChatWindow", "Group Chats", nullptr));
        pushButton_joinGroupChat->setText(QCoreApplication::translate("ChatWindow", "Join to Group Chat", nullptr));
        pushButton_AddGroupChat->setText(QCoreApplication::translate("ChatWindow", "Create group Chat", nullptr));
        pushButton->setText(QCoreApplication::translate("ChatWindow", "Add contact", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H

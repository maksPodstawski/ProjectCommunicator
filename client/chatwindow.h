#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QBuffer>
#include <QClipboard>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QMainWindow>
#include <QPixmap>
#include <QTextDocument>
#include <addcontact.h>
#include <addgroup.h>
#include <joingroup.h>
#include <program.h>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(Program *app, QWidget *parent = nullptr);
    ~ChatWindow();

private slots:
    void on_pushButton_clicked();
    void on_addContact(QListWidgetItem *item);
    void on_addGroup(QListWidgetItem *item);
    void on_clearContactList();

    void on_pushButton_logout_clicked();

    void on_pushButton_sendMessage_clicked();

    void on_listWidget_contacts_currentRowChanged(int currentRow);

    void loadChat();
    void on_updateChat();

    void on_pushButton_privateChats_clicked();

    void on_pushButton_groupChats_clicked();

    void on_pushButton_AddGroupChat_clicked();

    void on_pushButton_joinGroupChat_clicked();

    void on_listWidget_Groups_currentRowChanged(int currentRow);

    void on_listWidget_Groups_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_loadImage();

private:
    Ui::ChatWindow *ui;
    Program *mainApp = nullptr;
    AddContact *addContactWindow = nullptr;
    addGroup *addGroupWindow = nullptr;
    joinGroup *joinGroupWindow = nullptr;
    void loadContactImage();
};

#endif // CHATWINDOW_H

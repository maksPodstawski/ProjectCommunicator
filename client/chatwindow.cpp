#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(Program *app, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatWindow)
    , mainApp(app)
{
    ui->setupUi(this);
    QIcon icon("./img/logo.png");
    this->setWindowIcon(icon);
    QString username = mainApp->loggedUser->getUsername();
    QString title = "MatiMax - logged as " + username;
    this->setWindowTitle(title);
    connect(mainApp,SIGNAL(addContact(QListWidgetItem *)),this,SLOT(on_addContact(QListWidgetItem *)));
    connect(mainApp,SIGNAL(addGroup(QListWidgetItem *)),this,SLOT(on_addGroup(QListWidgetItem *)));
    connect(mainApp, SIGNAL(clearContactList()), this, SLOT(on_clearContactList()));
    connect(mainApp, SIGNAL(updateChat()), this, SLOT(on_updateChat()));
    connect(mainApp, SIGNAL(loadImage()), this, SLOT(on_loadImage()));
    ui->pushButton_sendMessage->setEnabled(false);
    ui->listWidget_contacts->show();
    ui->listWidget_Groups->hide();
    ui->pushButton_privateChats->setEnabled(false);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_pushButton_clicked()
{
    addContactWindow = new AddContact(nullptr);

    int result = addContactWindow->exec();
    if (result) {
        QString contactName = addContactWindow->getContactName();
        QString contactIP = addContactWindow->getContactIP();
        if (contactName.trimmed().isEmpty() || contactIP.trimmed().isEmpty()) {
            QMessageBox::warning(this, "Warning", "Labels can't be empty!");
        } else {
            if (mainApp->CheckIpIsValid(contactIP))
                mainApp->addContactToDB(contactName, contactIP);
        }
    }
    delete addContactWindow;
}

void ChatWindow::on_addContact(QListWidgetItem *item)
{
    ui->listWidget_contacts->addItem(item);
}

void ChatWindow::on_addGroup(QListWidgetItem *item)
{
    ui->listWidget_Groups->addItem(item);
}

void ChatWindow::on_clearContactList()
{
    ui->listWidget_contacts->clear();
    ui->listWidget_Groups->clear();
}

void ChatWindow::on_pushButton_logout_clicked()
{
    mainApp->LogoutUser();
}

void ChatWindow::on_pushButton_sendMessage_clicked()
{
    QString message = ui->lineEdit_message->text();
    int recieverIndex;
    if (!ui->pushButton_privateChats->isEnabled())
        recieverIndex = ui->listWidget_contacts->currentRow();
    else
        recieverIndex = ui->listWidget_Groups->currentRow();

    if (message.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Warning", "Message can't be empty!");
    } else if (!ui->pushButton_privateChats->isEnabled())
        mainApp->sendMessage(message, recieverIndex);
    else
        mainApp->sendGroupMessage(message, recieverIndex);

    ui->lineEdit_message->clear();
}

void ChatWindow::on_listWidget_contacts_currentRowChanged(int currentRow)
{
    qDebug() << "Zamieniona row ";
    mainApp->currentPrivateInex = currentRow;
    ui->pushButton_sendMessage->setEnabled(true);
    loadChat();
    ui->label_UserName->setText(mainApp->loggedUser->getUsername());
    ui->label_profileUser->setPixmap(mainApp->loggedUser->getProfile());
    loadContactImage();
}

void ChatWindow::loadChat()
{
    try {
        ui->listWidget_messages->clear();

        if (!ui->pushButton_privateChats->isEnabled()) {
            if (mainApp->currentPrivateInex >= 0) {
                for (auto message : mainApp->chats[mainApp->currentPrivateInex]->getMessages()) {
                    qDebug() << "Wiadomosc w loadchat: " << message->getMessageItem();
                    QListWidgetItem *item = new QListWidgetItem(message->getMessageItem());
                    ui->listWidget_messages->addItem(item);
                }
            }
        } else {
            if (mainApp->currentGroupIndex >= 0) {
                for (auto GroupMessage :
                     mainApp->groupChats[mainApp->currentGroupIndex]->getMessages()) {
                    qDebug() << "Wiadomosc w GROUP loadchat: " << GroupMessage->getMessageItem();
                    QListWidgetItem *item = new QListWidgetItem(GroupMessage->getMessageItem());
                    ui->listWidget_messages->addItem(item);
                }
            }
        }
        ui->listWidget_messages->scrollToBottom();
    } catch (...) {
        qDebug() << "Error ";
    }
}

void ChatWindow::on_updateChat()
{
    try {
        loadChat();
    } catch (...) {
        qDebug() << "Error ";
    }
}

void ChatWindow::on_pushButton_privateChats_clicked()
{
    ui->listWidget_contacts->show();
    ui->listWidget_Groups->hide();
    ui->pushButton_privateChats->setEnabled(false);
    ui->pushButton_groupChats->setEnabled(true);
    loadContactImage();
    loadChat();
}

void ChatWindow::on_pushButton_groupChats_clicked()
{
    ui->listWidget_contacts->hide();
    ui->listWidget_Groups->show();
    ui->pushButton_privateChats->setEnabled(true);
    ui->pushButton_groupChats->setEnabled(false);
    ui->label_profileContact->clear();
    ui->label_ContactName->clear();
    loadChat();
}

void ChatWindow::on_pushButton_AddGroupChat_clicked()
{
    addGroupWindow = new addGroup(nullptr);
    int result = addGroupWindow->exec();
    if (result)
    {
        QString groupChatName = addGroupWindow->getGroupName();
        if (groupChatName.trimmed().isEmpty())
            QMessageBox::warning(this, "Warning", "Group name can't be empty!");
        else
            mainApp->addGroupChatToDB(groupChatName);
    }
    delete addGroupWindow;
}

void ChatWindow::on_pushButton_joinGroupChat_clicked()
{
    joinGroupWindow = new joinGroup(nullptr);
    int result = joinGroupWindow->exec();

    if (result) {
        QString code = joinGroupWindow->getCode();
        QString name = joinGroupWindow->getName();
        if(code.trimmed().isEmpty() || name.trimmed().isEmpty())
            QMessageBox::warning(this, "Warning", "Group name or invite code cant be empty!");
        else
            mainApp->joinGroup(code, name);
    }
    delete joinGroupWindow;
}

void ChatWindow::on_listWidget_Groups_currentRowChanged(int currentRow)
{
    mainApp->currentGroupIndex = currentRow;
    ui->pushButton_sendMessage->setEnabled(true);
    loadChat();
}

void ChatWindow::on_listWidget_Groups_itemDoubleClicked(QListWidgetItem *item)
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString textToCopy = mainApp->groupChats[mainApp->currentGroupIndex]->getGroup()->getGroupCode();
    clipboard->setText(textToCopy);
}

void ChatWindow::on_pushButton_2_clicked()
{
    QString ImagePath = QFileDialog::getOpenFileName(this,
                                                     "Select profile picture",
                                                     "",
                                                     "JPG Files(*.jpg)");
    if (ImagePath.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Adding an avatar failed!");
        return;
    }
    QFileInfo FileInfo(ImagePath);
    QPixmap Image(ImagePath);
    QString ImageName = FileInfo.fileName();

    QString imageName = ImageName;

    int windowWidth = ui->label_profileUser->width();
    QPixmap scaledImage = Image.scaledToWidth(windowWidth, Qt::SmoothTransformation);

    ui->label_profileUser->setPixmap(scaledImage);

    mainApp->SaveImageToDB(scaledImage, imageName);
}

void ChatWindow::on_loadImage()
{
    loadContactImage();
}

void ChatWindow::loadContactImage()
{
    if (mainApp->currentPrivateInex >= 0) {
        if (!mainApp->contacts[mainApp->currentPrivateInex]->getProfile().isNull())
        {
            ui->label_profileContact->setPixmap(mainApp->contacts[mainApp->currentPrivateInex]->getProfile());
            ui->label_ContactName->setText(mainApp->contacts[mainApp->currentPrivateInex]->getUsername());
        }
        else {
            mainApp->sendImageRequest(mainApp->contacts[mainApp->currentPrivateInex]->getIP());
            ui->label_profileContact->clear();
            ui->label_ContactName->clear();
        }
    }
}

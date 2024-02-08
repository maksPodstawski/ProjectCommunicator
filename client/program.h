#ifndef PROGRAM_H
#define PROGRAM_H

#include <QBuffer>
#include <QDebug>
#include <QHostAddress>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QObject>
#include <QRandomGenerator>
#include <QTcpSocket>
#include "chat.h"
#include "group.h"
#include "message.h"
#include "user.h"

class MainWindow;

class User;

class Program : public QObject
{
    Q_OBJECT
public:
    explicit Program(QObject *parent = nullptr);
    void setGUI(MainWindow *ui = nullptr) { GUI = ui; }
    void CreateUserAccount(const QString &login, const QString &password, const QString &ip);
    void SendLoginRequest(const QString &login, const QString &password);
    bool CheckDataIsValid(const QString &login, const QString &password);
    bool CheckIpIsValid(const QString &ip);
    QString messageTypeToString(MessageType type);
    bool CheckIfResponseIsJson(const QString &response);
    User *loggedUser = nullptr;
    void addContactToDB(const QString &contactName, const QString &contactIP);
    QVector<User *> contacts;
    void UpdateContactList();
    void SendClientListRequest();
    void ReadContacts(const QJsonObject &responseObject);
    void LogoutUser();
    void sendMessage(const QString &message, const int &index);
    void AddMessageToChat(const QJsonObject &responseObject);
    QVector<Chat *> chats;
    int currentPrivateInex = -1;
    int currentGroupIndex = - 1;
    QString generateCode();
    void addGroupChatToDB(QString groupName);
    QVector<Group *> groups;
    QVector<GroupChat *> groupChats;
    void joinGroup(QString code, QString name);
    void sendGroupMessage(const QString &message, const int &index);
    void AddMessageToGroupChat(const QJsonObject &responseObject);
    void SaveImageToDB(QPixmap image, QString imageName);
    void sendImageRequest(const QString &ip);
    void handleFileMessage(const QString &data);

signals:
    void wrongIP();
    void wrongLogin();
    void wrongPassword();
    void noServerConnection();
    void loginFailed(QString info);
    void loginSuccessful();
    void addContact(QListWidgetItem *item);
    void clearContactList();
    void userLoggedOut();
    void updateChat();
    void addGroup(QListWidgetItem *item);
    void loadImage();

private:
    MainWindow *GUI = nullptr;
    QTcpSocket *m_TcpSocket;
    MessageType stringToMessageType(const QString &str);
    void LoginUser(const QJsonObject &responseObject);
    const QString m_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

private slots:
    void Read_Data_From_Socket();
};

#endif // PROGRAM_H

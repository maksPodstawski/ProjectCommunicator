#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtSql>
#include "connecteduser.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum class MessageType { login, reg, message, response, addContact, contactReq, contactList , addGroup, groupMessage, requestImage};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newConnection();
    void Read_Data_From_Socket();
    void Client_Disconnected();

private:
    Ui::MainWindow *ui;
    QTcpServer *TCP_Server;
    QTcpSocket *TCP_Socket;
    QList<connectedUser *> Client_Connection_List;
    void Add_New_Cilient_Connection(QTcpSocket *socket);
    void initializeDatabase();
    QSqlDatabase db;
    void createAccount(const QJsonObject &data, const QTcpSocket *socket);
    MessageType stringToMessageType(const QString &str);
    void checkIfUserIsLogged(const QJsonObject &data, const QTcpSocket *socket);
    void sendResponseToClient(const QString &username,
                              const QString &id,
                              const QString &ip,
                              const int &port,
                              const QString &additionalInfo = "");
    QString messageTypeToString(MessageType type);
    void sendMessageToSocket(const QString &jsonMessage, const int &port);
    void addContact(const QJsonObject &data);
    void addGroup(const QJsonObject &data);
    void saveGroupMessage(const QJsonObject &data);
    void sendContactsToClient(const QJsonObject &data, const QTcpSocket *socket);
    void saveAndSendMessage(const QJsonObject &data, const QTcpSocket *socket);
    int getUserIDbyIP(const QString &ip);
    void sendMessegeToUserById(const QJsonObject &data, const int id);
    void handleFileMessage(const QString &fileData);
    void readAndSendImage(const QJsonObject &data, const QTcpSocket *socket);
};
#endif // MAINWINDOW_H

#ifndef CONNECTEDUSER_H
#define CONNECTEDUSER_H

#include <QTcpSocket>

class connectedUser
{
    QTcpSocket *socket = nullptr;
    int userID = 0;

public:
    connectedUser();
    connectedUser(QTcpSocket *socket_, const int id)
        : socket(socket_)
        , userID(id)
    {}
    connectedUser(QTcpSocket *socket_)
        : socket(socket_)
    {}
    void setUserId(const int id) { userID = id; }
    int getUserID() { return userID; }
    QTcpSocket *getSocket() { return socket; }
};

#endif // CONNECTEDUSER_H

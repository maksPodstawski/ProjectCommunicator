#ifndef USER_H
#define USER_H

#include <QPixmap>
#include <QString>

class User
{
private:
    QString m_username;
    QString m_ip;
    int m_id;
    QPixmap m_profile;

public:
    User();
    User(const QString &username, const int &id);
    User(const QString &username, const QString &ip);
    User(const QString &username, const int &id, const QString &ip);
    void setProfile(const QPixmap &image);
    QPixmap getProfile() { return m_profile; };
    QString getUsername() { return m_username; }
    int getID() { return m_id; }
    QString getIP() { return m_ip; }
};

#endif // USER_H

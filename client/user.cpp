#include "user.h"

User::User() {}

User::User(const QString &username, const int &id)
    : m_username(username)
    , m_id(id)
{}

User::User(const QString &username, const QString &ip)
    : m_username(username)
    , m_ip(ip)
{}

User::User(const QString &username, const int &id, const QString &ip)
    : m_username(username)
    , m_id(id)
    , m_ip(ip)
{}

void User::setProfile(const QPixmap &image)
{
    m_profile = image;
}

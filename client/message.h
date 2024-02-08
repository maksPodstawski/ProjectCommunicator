#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDateTime>
#include <QString>

enum class MessageType {
    login,
    reg,
    message,
    response,
    addContact,
    contactReq,
    contactList,
    addGroup,
    groupMessage,
    requestImage
};

class Message
{
private:
    QString m_authorName;
    QDateTime m_timeStamp;
    QString m_message;

public:
    Message();
    Message(const QString &authorName, const QString &timeStamp, const QString message);
    QString getMessageItem();
};

#endif // MESSAGE_H

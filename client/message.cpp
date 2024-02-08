#include "message.h"

Message::Message() {}

Message::Message(const QString &authorName, const QString &timeStamp, const QString message)
    : m_authorName(authorName)
    , m_message(message)
{
    m_timeStamp = QDateTime::fromString(timeStamp, "dd-MM-yyyy hh:mm:ss");
}

QString Message::getMessageItem()
{
    return m_authorName + " " + m_timeStamp.toString("dd-MM-yyyy hh:mm:ss") + "\n" + m_message
           + "\n\n";
}

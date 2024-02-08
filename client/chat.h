#ifndef CHAT_H
#define CHAT_H

#include <QDebug>
#include <QVector>
#include "group.h"
#include "message.h"
#include "user.h"

class Chat
{
protected:
    User *chatWith = nullptr;
    QVector<Message *> m_messages;

public:
    Chat();
    User *getUser() { return chatWith; }
    QVector<Message *> getMessages() { return m_messages; }
    Chat(User *);
    ~Chat();
    void addMessage(Message *message);
};

class GroupChat : public Chat
{
    Group *group = nullptr;

public:
    GroupChat(Group *);
    ~GroupChat();
    Group *getGroup() { return group; }
};

#endif // CHAT_H

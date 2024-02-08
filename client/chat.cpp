#include "chat.h"

Chat::Chat() {}

Chat::Chat(User *user)
{
    chatWith = user;
}

Chat::~Chat()
{
    while (m_messages.count())
        delete m_messages.takeLast();
    delete chatWith;
}

void Chat::addMessage(Message *message)
{
    this->m_messages.append(message);
}

GroupChat::GroupChat(Group *gr)
{
    group = gr;
}

GroupChat::~GroupChat()
{
    delete group;
}

#include "program.h"
#include "qbuffer.h"

Program::Program(QObject *parent)
    : QObject{parent}
{
    m_TcpSocket = new QTcpSocket();
    m_TcpSocket->connectToHost(QHostAddress("192.168.0.10"), 2137);
    m_TcpSocket->open(QIODevice::ReadWrite);

    connect(m_TcpSocket, SIGNAL(readyRead()), this, SLOT(Read_Data_From_Socket()));
}

void Program::CreateUserAccount(const QString &login, const QString &password, const QString &ip)
{
    qDebug() << ip;
    if (m_TcpSocket->isOpen()) {
        QJsonObject createAccountObject;
        createAccountObject["messageType"] = messageTypeToString(MessageType::reg);
        createAccountObject["login"] = login;
        createAccountObject["password"] = password;
        createAccountObject["ip"] = ip;

        QJsonDocument createAccountDocument(createAccountObject);
        QString createAccountJson = createAccountDocument.toJson();
        m_TcpSocket->write(createAccountJson.toStdString().c_str());
    }
}

void Program::SendLoginRequest(const QString &login, const QString &password)
{
    if (m_TcpSocket->isOpen()) {
        QJsonObject loginRequestObject;
        loginRequestObject["messageType"] = messageTypeToString(MessageType::login);
        loginRequestObject["login"] = login;
        loginRequestObject["password"] = password;

        QJsonDocument loginRequestDocument(loginRequestObject);
        QString loginRequestJson = loginRequestDocument.toJson();
        m_TcpSocket->write(loginRequestJson.toStdString().c_str());
    } else {
        emit noServerConnection();
    }
}

bool Program::CheckDataIsValid(const QString &login, const QString &password)
{
    if (login.trimmed().isEmpty()) {
        emit wrongLogin();
        return false;
    }
    if (password.trimmed().isEmpty()) {
        emit wrongPassword();
        return false;
    }
    return true;
}

bool Program::CheckIpIsValid(const QString &ip)
{
    QHostAddress address(ip);
    if (QAbstractSocket::IPv4Protocol != address.protocol()) {
        emit wrongIP();
        return false;
    }
    return true;
}

QString Program::messageTypeToString(MessageType type)
{
    switch (type) {
    case MessageType::reg:
        return "register";
    case MessageType::login:
        return "login";
    case MessageType::message:
        return "message";
    case MessageType::response:
        return "response";
    case MessageType::addContact:
        return "addContact";
    case MessageType::contactReq:
        return "contactReq";
    case MessageType::contactList:
        return "contactList";
    case MessageType::addGroup:
        return "addGroup";
    case MessageType::groupMessage:
        return "groupMessage";
    case MessageType::requestImage:
        return "requestImage";
    }
}

bool Program::CheckIfResponseIsJson(const QString &response)
{
    QJsonDocument responseDocument = QJsonDocument::fromJson(response.toUtf8());
    if (!responseDocument.isNull() && responseDocument.isObject()) {
        QJsonObject responseObject = responseDocument.object();
        return responseObject.contains("messageType");
    } else
        return false;
}

void Program::addContactToDB(const QString &contactName, const QString &contactIP)
{
    if (m_TcpSocket->isOpen()) {
        qDebug() << "logged user id: " << loggedUser->getID();
        QJsonObject addContactObject;
        addContactObject["messageType"] = messageTypeToString(MessageType::addContact);
        addContactObject["contactName"] = contactName;
        addContactObject["contactIP"] = contactIP;
        addContactObject["id"] = loggedUser->getID();

        QJsonDocument addContactDocument(addContactObject);
        QString addContactJson = addContactDocument.toJson();
        m_TcpSocket->write(addContactJson.toStdString().c_str());

        User *new_contact = new User(contactName, contactIP);
        contacts.append(new_contact);
        Chat *new_chat = new Chat(new_contact);
        chats.append(new_chat);

        UpdateContactList();
    } else {
        emit noServerConnection();
    }
}

void Program::UpdateContactList()
{
    emit clearContactList();
    for (auto contact : contacts) {
        QListWidgetItem *item = new QListWidgetItem(contact->getUsername());
        emit addContact(item);
    }
    for (auto group : groups) {
        QListWidgetItem *item = new QListWidgetItem(group->getGroupName());
        emit addGroup(item);
    }
}

void Program::SendClientListRequest()
{
    if (m_TcpSocket->isOpen()) {
        qDebug() << "logged user id: " << loggedUser->getID();
        QJsonObject contactReqObject;
        contactReqObject["messageType"] = messageTypeToString(MessageType::contactReq);
        contactReqObject["id"] = loggedUser->getID();
        QJsonDocument contactReqDocument(contactReqObject);
        QString contactReqJson = contactReqDocument.toJson();
        m_TcpSocket->write(contactReqJson.toStdString().c_str());
    } else {
        emit noServerConnection();
    }
}

void Program::ReadContacts(const QJsonObject &responseObject)
{
    QJsonArray contactArray = responseObject["contacts"].toArray();

    for (const QJsonValue &contactValue : contactArray) {
        QJsonObject contactObject = contactValue.toObject();
        QString contactIP = contactObject["contactIP"].toString();
        QString contactName = contactObject["contactName"].toString();

        User *new_contact = new User(contactName, contactIP);
        contacts.append(new_contact);
        Chat *new_chat = new Chat(new_contact);
        chats.append(new_chat);

        QJsonArray messageArray = contactObject["messages"].toArray();
        for (const QJsonValue &messageValue : messageArray) {
            QJsonObject messageObject = messageValue.toObject();
            QString authorName = messageObject["authorName"].toString();
            QString messageText = messageObject["message"].toString();
            QString timeStamp = messageObject["timeStamp"].toString();

            Message *new_message = new Message(authorName, timeStamp, messageText);
            new_chat->addMessage(new_message);
        }
    }

    QJsonArray groupsArray = responseObject["groups"].toArray();

    for (const QJsonValue &groupValue : groupsArray) {
        QJsonObject groupObject = groupValue.toObject();
        QString groupCode = groupObject["groupCode"].toString();
        QString groupName = groupObject["groupName"].toString();

        Group *new_group = new Group(groupName, groupCode);
        groups.append(new_group);

        GroupChat *new_groupChat = new GroupChat(new_group);
        groupChats.append(new_groupChat);

        QJsonArray messageArray = groupObject["groupMessages"].toArray();
        for (const QJsonValue &messageValue : messageArray) {
            QJsonObject messageObject = messageValue.toObject();
            QString authorName = messageObject["authorName"].toString();
            QString messageText = messageObject["message"].toString();
            QString timeStamp = messageObject["timeStamp"].toString();

            Message *new_message = new Message(authorName, timeStamp, messageText);
            new_groupChat->addMessage(new_message);
        }
    }
    UpdateContactList();
    sendImageRequest(loggedUser->getIP());
}

void Program::LogoutUser()
{
    loggedUser = nullptr;
    contacts.clear();
    chats.clear();
    groupChats.clear();
    groups.clear();
    emit userLoggedOut();
}

void Program::sendMessage(const QString &message, const int &index)
{
    QString receiverIP = contacts[index]->getIP();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString time = currentDateTime.toString("dd-MM-yyyy hh:mm:ss");
    if (m_TcpSocket->isOpen()) {
        qDebug() << "receiverIP: " << receiverIP;
        QJsonObject messageObject;
        messageObject["messageType"] = messageTypeToString(MessageType::message);
        messageObject["id"] = loggedUser->getID();
        messageObject["authorName"] = loggedUser->getUsername();
        messageObject["timeStamp"] = time;
        messageObject["receiverIP"] = receiverIP;
        messageObject["message"] = message;
        messageObject["authorIP"] = loggedUser->getIP();
        QJsonDocument messageDocument(messageObject);
        QString messageJson = messageDocument.toJson();
        m_TcpSocket->write(messageJson.toStdString().c_str());
    } else {
        emit noServerConnection();
    }
}

void Program::AddMessageToChat(const QJsonObject &responseObject)
{
    QString authorName = responseObject["authorName"].toString();
    QString message = responseObject["message"].toString();
    QString timeStamp = responseObject["timeStamp"].toString();
    QString authorIP = responseObject["authorIP"].toString();
    QString receiverIP = responseObject["receiverIP"].toString();

    Message *new_message = new Message(authorName, timeStamp, message);

    if (authorIP == loggedUser->getIP()) {
        for (auto chat : chats) {
            if (chat->getUser()->getIP() == receiverIP) {
                chat->addMessage(new_message);
                qDebug() << "DODANO: " << new_message->getMessageItem();
                emit updateChat();
                return;
            }
        }
    } else {
        for (auto chat : chats) {
            if (chat->getUser()->getIP() == authorIP) {
                chat->addMessage(new_message);
                qDebug() << "DODANO: " << new_message->getMessageItem();
                emit updateChat();
                return;
            }
        }
    }
    delete new_message;
}

QString Program::generateCode()
{
    QString code;
    for (int i = 0; i < 8; i++) {
        int index = QRandomGenerator::global()->bounded(m_characters.length());
        code.append(m_characters.at(index));
    }
    return code;
}

void Program::addGroupChatToDB(QString groupName)
{
    QString code = generateCode();
    if (m_TcpSocket->isOpen()) {
        qDebug() << "logged user id: " << loggedUser->getID();
        QJsonObject addGroupObject;
        addGroupObject["messageType"] = messageTypeToString(MessageType::addGroup);
        addGroupObject["groupName"] = groupName;
        addGroupObject["code"] = code;
        addGroupObject["id"] = loggedUser->getID();

        QJsonDocument addGroupDocument(addGroupObject);
        QString addGroupJson = addGroupDocument.toJson();
        m_TcpSocket->write(addGroupJson.toStdString().c_str());

        Group *new_group = new Group(groupName, code);
        groups.append(new_group);

        GroupChat *new_GroupChat = new GroupChat(new_group);
        groupChats.append(new_GroupChat);

        UpdateContactList();
    } else {
        emit noServerConnection();
    }
}

void Program::joinGroup(QString code, QString name)
{
    if (m_TcpSocket->isOpen()) {
        qDebug() << "logged user id: " << loggedUser->getID();
        QJsonObject addGroupObject;
        addGroupObject["messageType"] = messageTypeToString(MessageType::addGroup);
        addGroupObject["groupName"] = name;
        addGroupObject["code"] = code;
        addGroupObject["id"] = loggedUser->getID();

        QJsonDocument addGroupDocument(addGroupObject);
        QString addGroupJson = addGroupDocument.toJson();
        m_TcpSocket->write(addGroupJson.toStdString().c_str());

        Group *new_group = new Group(name, code);
        groups.append(new_group);

        GroupChat *new_GroupChat = new GroupChat(new_group);
        groupChats.append(new_GroupChat);

        UpdateContactList();
    } else {
        emit noServerConnection();
    }
}

void Program::sendGroupMessage(const QString &message, const int &index)
{
    QString groupCode = groups[index]->getGroupCode();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString time = currentDateTime.toString("dd-MM-yyyy hh:mm:ss");
    if (m_TcpSocket->isOpen()) {
        qDebug() << "receiverIP: " << groupCode;
        QJsonObject groupMessageObject;
        groupMessageObject["messageType"] = messageTypeToString(MessageType::groupMessage);
        groupMessageObject["id"] = loggedUser->getID();
        groupMessageObject["authorName"] = loggedUser->getUsername();
        groupMessageObject["timeStamp"] = time;
        groupMessageObject["groupCode"] = groupCode;
        groupMessageObject["message"] = message;
        groupMessageObject["authorIP"] = loggedUser->getIP();
        QJsonDocument groupMessageDocument(groupMessageObject);
        QString groupMessageJson = groupMessageDocument.toJson();
        m_TcpSocket->write(groupMessageJson.toStdString().c_str());
    } else {
        emit noServerConnection();
    }
}

void Program::AddMessageToGroupChat(const QJsonObject &responseObject)
{
    QString authorName = responseObject["authorName"].toString();
    QString message = responseObject["message"].toString();
    QString timeStamp = responseObject["timeStamp"].toString();
    QString groupCode = responseObject["groupCode"].toString();

    Message *new_groupMessage = new Message(authorName, timeStamp, message);

    for (auto groupChat : groupChats) {
        if (groupChat->getGroup()->getGroupCode() == groupCode) {
            groupChat->addMessage(new_groupMessage);
            emit updateChat();
            return;
        }
    }
    delete new_groupMessage;
}

void Program::SaveImageToDB(QPixmap image, QString imageName)
{
    QBuffer ImageBufferData;
    if (ImageBufferData.open(QIODevice::ReadWrite)) {
        image.save(&ImageBufferData, "JPG");
    }
    QByteArray ImageArr = ImageBufferData.buffer().toBase64();
    QString header = "PROFILE " + QString::number(loggedUser->getID()) + "\n";
    QString finalMessage = header + ImageArr;
    m_TcpSocket->write(finalMessage.toStdString().c_str());
}

void Program::sendImageRequest(const QString &ip)
{
    if (m_TcpSocket->isOpen()) {
        QJsonObject ImageRequestObject;
        ImageRequestObject["messageType"] = messageTypeToString(MessageType::requestImage);
        ImageRequestObject["IP"] = ip;
        QJsonDocument ImageRequestDocument(ImageRequestObject);
        QString ImageRequestJson = ImageRequestDocument.toJson();
        m_TcpSocket->write(ImageRequestJson.toStdString().c_str());
    } else {
        emit noServerConnection();
    }
}

void Program::handleFileMessage(const QString &data)
{
    QStringList lines = data.split("\n");

    if (lines.isEmpty()) {
        qDebug() << "Brak linii";
        return;
    }

    QString firstLine = lines.first();
    qDebug() << "Pierwsza linia:" << firstLine;

    QStringList words = firstLine.split(" ");
    QString ip;
    QPixmap image;
    if (words.size() >= 2 && words.first() == "PROFILE") {
        ip = words.at(1);
        words.removeFirst();
        words.removeFirst();

        QString data = lines[1].toUtf8();
        QByteArray ImageData = QByteArray::fromBase64(data.toUtf8());
        image.loadFromData(ImageData, "JPG");
    }
    if (ip == loggedUser->getIP()) {
        qDebug() << "Setting image";
        loggedUser->setProfile(image);
    } else {
        for (auto user : contacts) {
            qDebug() << "Setting  contact image";
            if (user->getIP() == ip)
                user->setProfile(image);
        }
        emit loadImage();
    }
}

MessageType Program::stringToMessageType(const QString &str)
{
    if (str == "register")
        return MessageType::reg;
    else if (str == "login")
        return MessageType::login;
    else if (str == "message")
        return MessageType::message;
    else if (str == "response")
        return MessageType::response;
    else if (str == "addContact")
        return MessageType::addContact;
    else if (str == "contactReq")
        return MessageType::contactReq;
    else if (str == "contactList")
        return MessageType::contactList;
    else if (str == "addGroup")
        return MessageType::addGroup;
    else if (str == "groupMessage")
        return MessageType::groupMessage;
    else if (str == "requestImage")
        return MessageType::requestImage;
}

void Program::LoginUser(const QJsonObject &responseObject)
{
    QString username = responseObject["username"].toString();
    int id = responseObject["id"].toString().toInt();
    QString ip = responseObject["ip"].toString();
    qDebug() << "LoginUser ip: " << ip;
    if (!responseObject["additionalInfo"].toString().isEmpty()) {
        qDebug() << responseObject["additionalInfo"].toString();
        emit loginFailed(responseObject["additionalInfo"].toString());
    } else {
        qDebug() << "User " << username << " logged in";
        loggedUser = new User(username, id, ip);
        emit loginSuccessful();
        SendClientListRequest();
    }
}

void Program::Read_Data_From_Socket()
{
    QByteArray Data_From_Server = m_TcpSocket->readAll();
    QString receivedData = QString::fromUtf8(Data_From_Server);
    qDebug() << receivedData;
    if (CheckIfResponseIsJson(receivedData)) {
        qDebug() << receivedData;
        QJsonDocument responseDocument = QJsonDocument::fromJson(receivedData.toUtf8());
        QJsonObject responseObject = responseDocument.object();
        if (stringToMessageType(responseObject["messageType"].toString()) == MessageType::response) {
            LoginUser(responseObject);
        } else if (stringToMessageType(responseObject["messageType"].toString())
                   == MessageType::contactList) {
            ReadContacts(responseObject);
        } else if (stringToMessageType(responseObject["messageType"].toString())
                   == MessageType::message) {
            AddMessageToChat(responseObject);
        } else if (stringToMessageType(responseObject["messageType"].toString())
                   == MessageType::groupMessage) {
            AddMessageToGroupChat(responseObject);
        }
    } else {
        handleFileMessage(receivedData);
    }
}

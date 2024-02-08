#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TCP_Server = new QTcpServer();
    if (TCP_Server->listen(QHostAddress("192.168.1.16"), 2137)) {
        connect(TCP_Server, SIGNAL(newConnection()), this, SLOT(newConnection()));
        QMessageBox::information(this, "Alert", "Server start successful");
    } else {
        QMessageBox::information(this, "Alert", "Server start fail");
    }

    initializeDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Add_New_Cilient_Connection(QTcpSocket *socket)
{
    connectedUser *new_user = new connectedUser(socket);
    Client_Connection_List.append(new_user);
    connect(socket, SIGNAL(readyRead()), this, SLOT(Read_Data_From_Socket()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(Client_Disconnected()));
    ui->comboBox_Client_List->addItem(QString::number(socket->socketDescriptor()));
    QString Client = "Client : " + QString::number(socket->socketDescriptor())
                     + " Connected With The Server";
    ui->textEdit_Client_Messages->append(Client);
}

void MainWindow::initializeDatabase()
{
    QString dbPath = "database.db";

    if (!QFile::exists(dbPath)) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbPath);

        if (!db.open()) {
            qWarning() << "Could not open the database!";
            return;
        }

        QSqlQuery query;
        if (!query.exec("CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT "
                        "UNIQUE, password TEXT, ip TEXT UNIQUE, image BLOB)")) {
            qWarning() << "Error creating users table:" << query.lastError().text();
            return;
        }

        if (!query.exec("CREATE TABLE contacts (num INTEGER PRIMARY KEY AUTOINCREMENT, userID "
                        "INTEGER, contactName TEXT, contactIP TEXT)")) {
            qWarning() << "Error creating contacts table:" << query.lastError().text();
            return;
        }

        if (!query.exec("CREATE TABLE messages (num INTEGER PRIMARY KEY AUTOINCREMENT, authorID "
                        "INTEGER, receiverID INTEGER, authorName TEXT, message TEXT, receiverIP "
                        "TEXT, timeStamp TEXT, authorIP TEXT)")) {
            qWarning() << "Error creating messages table:" << query.lastError().text();
            return;
        }

        if (!query.exec("CREATE TABLE groups (num INTEGER PRIMARY KEY AUTOINCREMENT, userID "
                        "INTEGER, groupCode TEXT, groupName TEXT)")) {
            qWarning() << "Error creating groups table:" << query.lastError().text();
            return;
        }

        if (!query.exec("CREATE TABLE groupMessages (num INTEGER PRIMARY KEY AUTOINCREMENT, userID INTEGER, groupCode TEXT, authorName TEXT,timeStamp TEXT, message TEXT)")) {
            qWarning() << "Error creating groupMessages table:" << query.lastError().text();
            return;
        }

        qDebug() << "Created a new database and the users table.";
    } else {
        qDebug() << "The database already exists.";
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbPath);

        if (!db.open()) {
            qWarning() << "Could not open the database!";
            return;
        }
    }
}

void MainWindow::createAccount(const QJsonObject &data, const QTcpSocket *socket)
{
    QString login = data["login"].toString();
    QString password = data["password"].toString();
    QString ip = data["ip"].toString();
    if (!db.isOpen())
        return;
    QSqlQuery createAccountQry;
    createAccountQry.prepare(
        "INSERT INTO users (username, password, ip) VALUES (:username, :password, :ip)");
    createAccountQry.bindValue(":username", login);
    createAccountQry.bindValue(":password", password);
    createAccountQry.bindValue(":ip", ip);
    if (createAccountQry.exec()) {
        qDebug() << "Account Created Successfully";
        checkIfUserIsLogged(data, socket);
    } else {
        qDebug() << "Account Creation Failed!";
    }
}

MessageType MainWindow::stringToMessageType(const QString &str)
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

void MainWindow::checkIfUserIsLogged(const QJsonObject &data, const QTcpSocket *socket)
{
    QString login = data["login"].toString();
    QString password = data["password"].toString();
    if (!db.isOpen())
        return;
    QSqlQuery checkQry;
    checkQry.prepare(
        "SELECT id, username, ip FROM users WHERE username = :username AND password = :password");
    checkQry.bindValue(":username", login);
    checkQry.bindValue(":password", password);
    if (checkQry.exec()) {
        if (checkQry.next()) {
            QString id = checkQry.value("id").toString();
            QString username = checkQry.value("username").toString();
            QString ip = checkQry.value("ip").toString();
            qDebug() << "IP przy sprawdzamiu:" << ip;
            sendResponseToClient(username, id, ip, socket->socketDescriptor());
        } else {
            sendResponseToClient("",
                                 "",
                                 "",
                                 socket->socketDescriptor(),
                                 "Login or Password is Wrong!");
        }
    }
}

void MainWindow::sendResponseToClient(const QString &username,
                                      const QString &id,
                                      const QString &ip,
                                      const int &port,
                                      const QString &additionalInfo)
{
    QJsonObject responseObject;
    responseObject["username"] = username;
    responseObject["id"] = id;
    responseObject["ip"] = ip;
    responseObject["additionalInfo"] = additionalInfo;
    responseObject["messageType"] = messageTypeToString(MessageType::response);
    QJsonDocument responseDocument(responseObject);
    QString responseJson = responseDocument.toJson();
    sendMessageToSocket(responseJson, port);
}

QString MainWindow::messageTypeToString(MessageType type)
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

void MainWindow::sendMessageToSocket(const QString &jsonMessage, const int &port)
{
    for (auto user : Client_Connection_List) {
        int portId = user->getSocket()->socketDescriptor();
        if (portId == port) {
            user->getSocket()->write(jsonMessage.toStdString().c_str());
        }
    }
}

void MainWindow::addContact(const QJsonObject &data)
{
    QString contactName = data["contactName"].toString();
    QString contactIP = data["contactIP"].toString();
    int id = data["id"].toInt();
    if (!db.isOpen())
        return;
    QSqlQuery addContactQry;
    addContactQry.prepare("INSERT INTO contacts (userID, contactName, contactIP) VALUES (:userID, "
                          ":contactName, :contactIP)");
    addContactQry.bindValue(":userID", id);
    addContactQry.bindValue(":contactName", contactName);
    addContactQry.bindValue(":contactIP", contactIP);
    if (addContactQry.exec()) {
        qDebug() << "Contact Added Successfully";
    } else {
        qDebug() << "Contact Addeding Failed!";
    }
}

void MainWindow::addGroup(const QJsonObject &data)
{
    QString groupName = data["groupName"].toString();
    QString groupCode = data["code"].toString();
    int id = data["id"].toInt();
    if (!db.isOpen())
        return;
    QSqlQuery addGroupQry;
    addGroupQry.prepare("INSERT INTO groups (userID, groupCode, groupName) VALUES (:userID, "
                          ":groupCode, :groupName)");
    addGroupQry.bindValue(":userID", id);
    addGroupQry.bindValue(":groupCode", groupCode);
    addGroupQry.bindValue(":groupName", groupName);
    if (addGroupQry.exec()) {
        qDebug() << "Group Added Successfully";
    } else {
        qDebug() << "Group Addeding Failed!";
    }
}

void MainWindow::saveGroupMessage(const QJsonObject &data)
{
    QString authorName = data["authorName"].toString();
    QString timeStamp = data["timeStamp"].toString();
    QString message = data["message"].toString();
    QString groupCode = data["groupCode"].toString();
    int id = data["id"].toInt();
    if (!db.isOpen())
        return;
    QSqlQuery addGroupMessageQry;
    addGroupMessageQry.prepare("INSERT INTO groupMessages (userID, groupCode, authorName, timeStamp, message) VALUES (:userID, :groupCode, :authorName, :timeStamp, :message)");
    addGroupMessageQry.bindValue(":userID", id);
    addGroupMessageQry.bindValue(":groupCode", groupCode);
    addGroupMessageQry.bindValue(":authorName", authorName);
    addGroupMessageQry.bindValue(":timeStamp", timeStamp);
    addGroupMessageQry.bindValue(":message", message);
    if (addGroupMessageQry.exec()) {
        qDebug() << "GroupMessage Added Successfully";
        QSqlQuery idByCodeQry;
        idByCodeQry.prepare("SELECT userID FROM groups WHERE groupCode = :groupCode");
        idByCodeQry.bindValue(":groupCode", groupCode);
        if (idByCodeQry.exec())
        {
            while (idByCodeQry.next())
            {
                int id = idByCodeQry.value("userID").toInt();
                sendMessegeToUserById(data, id);
            }
        }

    } else {
        qDebug() << "GroupMessage Addeding Failed!";
    }

}

void MainWindow::sendContactsToClient(const QJsonObject &data, const QTcpSocket *socket)
{
    int id = data["id"].toInt();

    for (auto user : Client_Connection_List) {
        if (user->getSocket() == socket)
            user->setUserId(id);
    }

    QSqlQuery contactListQry;
    contactListQry.prepare("SELECT contactName, contactIP FROM contacts WHERE userID = :id");
    contactListQry.bindValue(":id", id);
    QJsonArray contactsArray;
    QJsonArray messageArray;

    if (contactListQry.exec())
    {
        while (contactListQry.next())
        {
            QString contactName = contactListQry.value("contactName").toString();
            QString contactIP = contactListQry.value("contactIP").toString();
            QSqlQuery messageListQry;
            messageListQry.prepare("SELECT message, authorName, timeStamp FROM messages WHERE (authorID = :aid AND receiverID = :rid) OR (authorID = :rid AND receiverID = :aid)");
            messageListQry.bindValue(":aid", id);
            messageListQry.bindValue(":rid", getUserIDbyIP(contactIP));


            if(messageListQry.exec())
            {
            while (messageListQry.next())
                {
                QString message = messageListQry.value("message").toString();
                QString authorName = messageListQry.value("authorName").toString();
                QString timeStamp = messageListQry.value("timeStamp").toString();
                QJsonObject messageObject;
                messageObject["message"] = message;
                messageObject["authorName"] = authorName;
                messageObject["timeStamp"] = timeStamp;
                messageArray.append(messageObject);
                }
            }

            QJsonObject contactObject;
            contactObject["contactName"] = contactName;
            contactObject["contactIP"] = contactIP;
            contactObject["messages"] = messageArray;
            contactsArray.append(contactObject);
        }
    }

    QSqlQuery groupListQry;
    QJsonArray groupsArray;


    groupListQry.prepare("SELECT groupCode, groupName FROM groups WHERE userID = :id");
    groupListQry.bindValue(":id", id);

    if(groupListQry.exec())
    {
        while (groupListQry.next())
        {
            QString groupCode = groupListQry.value("groupCode").toString();
            QString groupName = groupListQry.value("groupName").toString();
            QJsonArray groupMessagesArray;

            QSqlQuery groupMessageListQry;
            groupMessageListQry.prepare("SELECT message, authorName, timeStamp FROM groupMessages WHERE groupCode = :groupCode");
            groupMessageListQry.bindValue(":groupCode", groupCode);

            if(groupMessageListQry.exec())
            {
                while (groupMessageListQry.next())
                {
                    QString message = groupMessageListQry.value("message").toString();
                    QString authorName = groupMessageListQry.value("authorName").toString();
                    QString timeStamp = groupMessageListQry.value("timeStamp").toString();
                    QJsonObject groupMessageObject;
                    groupMessageObject["message"] = message;
                    groupMessageObject["authorName"] = authorName;
                    groupMessageObject["timeStamp"] = timeStamp;
                    groupMessagesArray.append(groupMessageObject);
                }
            }

            QJsonObject groupObject;
            groupObject["groupCode"] = groupCode;
            groupObject["groupName"] = groupName;
            groupObject["groupMessages"] = groupMessagesArray;
            groupsArray.append(groupObject);
        }
    }


    QJsonObject resultObject;
    resultObject["contacts"] = contactsArray;
    resultObject["groups"] = groupsArray;
    resultObject["messageType"] = messageTypeToString(MessageType::contactList);

    QJsonDocument jsonDocument(resultObject);
    QString jsonString = jsonDocument.toJson();
    sendMessageToSocket(jsonString, socket->socketDescriptor());
}


void MainWindow::saveAndSendMessage(const QJsonObject &data, const QTcpSocket *socket)
{
    int authorId = data["id"].toInt();
    QString authorName = data["authorName"].toString();
    QString message = data["message"].toString();
    QString timeStamp = data["timeStamp"].toString();
    QString receiverIP = data["receiverIP"].toString();
    QString authorIP = data["authorIP"].toString();
    int receiverID = getUserIDbyIP(receiverIP);
    QSqlQuery addMessageQry;
    addMessageQry.prepare("INSERT INTO messages (authorID, receiverID, authorName, message, "
                          "receiverIP, timeStamp, authorIP) VALUES (:authorID, :receiverID, "
                          ":authorName, :message, :receiverIP, :timeStamp, :authorIP)");
    addMessageQry.bindValue(":authorID", authorId);
    addMessageQry.bindValue(":receiverID", receiverID);
    addMessageQry.bindValue(":authorName", authorName);
    addMessageQry.bindValue(":message", message);
    addMessageQry.bindValue(":receiverIP", receiverIP);
    addMessageQry.bindValue(":timeStamp", timeStamp);
    addMessageQry.bindValue(":authorIP", authorIP);
    if (addMessageQry.exec()) {
        qDebug() << "Message Added Successfully";
        sendMessegeToUserById(data, authorId);
        sendMessegeToUserById(data, receiverID);
    } else {
        qDebug() << "Message Addeding Failed!";
    }
}

int MainWindow::getUserIDbyIP(const QString &ip)
{
    QSqlQuery getIdQuery;
    getIdQuery.prepare("SELECT id FROM users WHERE ip = :ip");
    getIdQuery.bindValue(":ip", ip);
    if (getIdQuery.exec()) {
        if (getIdQuery.next()) {
            int id = getIdQuery.value("id").toInt();
            return id;
        }
    }
    return 0;
}

void MainWindow::sendMessegeToUserById(const QJsonObject &data, const int id)
{
    QJsonDocument messageDocument(data);
    QString messageJson = messageDocument.toJson();
    for (auto user : Client_Connection_List) {
        if (user->getUserID() == id)
            sendMessageToSocket(messageJson, user->getSocket()->socketDescriptor());
    }
}

void MainWindow::handleFileMessage(const QString &fileData)
{
    QStringList lines = fileData.split("\n");

    if (lines.isEmpty()) {
        qDebug() << "Brak linii";
        return;
    }

    QString firstLine = lines.first();
    qDebug() << "Pierwsza linia:" << firstLine;

    QStringList words = firstLine.split(" ");

    if (words.size() >= 2 && words.first() == "PROFILE") {
        QString id = words.at(1);
        words.removeFirst();
        words.removeFirst();

        QByteArray data = lines[1].toUtf8();

        QSqlQuery addImage;
        addImage.prepare("UPDATE users SET image = :image WHERE id = :id");
        addImage.bindValue(":image", data);
        addImage.bindValue(":id", id);
        if (addImage.exec()) {
            qDebug() << "Profile added";
        }
        return;
    } else {
        qDebug() << "Pierwsze słowo nie jest PROFILE";
        return;
    }
}

void MainWindow::readAndSendImage(const QJsonObject &data, const QTcpSocket *socket)
{
    QString ip = data["IP"].toString();
    int id = getUserIDbyIP(ip);

    QSqlQuery getImageQry;
    getImageQry.prepare("SELECT image FROM users WHERE id = :id");
    getImageQry.bindValue(":id", id);

    QByteArray imageData;

    if(getImageQry.exec())
    {
        while (getImageQry.next())
        {
            imageData = getImageQry.value("image").toByteArray();
            qDebug() << imageData;
        }
    }
    if(!imageData.isNull())
    {
        QString header = "PROFILE " + ip + "\n";
        QString finalMessage = header + imageData;
        sendMessageToSocket(finalMessage, socket->socketDescriptor());
    }

}


void MainWindow::newConnection()
{
    while (TCP_Server->hasPendingConnections()) {
        Add_New_Cilient_Connection(TCP_Server->nextPendingConnection());
    }
}

void MainWindow::Read_Data_From_Socket()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket) {
        QByteArray data = socket->readAll();
        QString receivedData = QString::fromUtf8(data);
        ui->textEdit_Client_Messages->append(receivedData);
        QJsonDocument receivedDataDocument = QJsonDocument::fromJson(receivedData.toUtf8());
        if (!receivedDataDocument.isNull() && receivedDataDocument.isObject()) {
            QJsonObject receivedDataObject = receivedDataDocument.object();

            if (receivedDataObject.contains("messageType")) {
                if (stringToMessageType(receivedDataObject["messageType"].toString())
                    == MessageType::reg)
                    createAccount(receivedDataObject, socket);
                else if (stringToMessageType(receivedDataObject["messageType"].toString())
                         == MessageType::login)
                    checkIfUserIsLogged(receivedDataObject, socket);
                else if (stringToMessageType(receivedDataObject["messageType"].toString())
                         == MessageType::addContact)
                    addContact(receivedDataObject);
                else if (stringToMessageType(receivedDataObject["messageType"].toString())
                         == MessageType::contactReq)
                    sendContactsToClient(receivedDataObject, socket);
                else if (stringToMessageType(receivedDataObject["messageType"].toString())
                         == MessageType::message)
                    saveAndSendMessage(receivedDataObject, socket);
                else if (stringToMessageType(receivedDataObject["messageType"].toString()) == MessageType::addGroup)
                    addGroup(receivedDataObject);
                else if (stringToMessageType(receivedDataObject["messageType"].toString()) == MessageType::groupMessage)
                    saveGroupMessage(receivedDataObject);
                else if (stringToMessageType(receivedDataObject["messageType"].toString()) == MessageType::requestImage)
                    readAndSendImage(receivedDataObject, socket);
            }
        }
        else
        {
            handleFileMessage(receivedData);
        }
    }
}

void MainWindow::Client_Disconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket) {
        int index;
        for (auto user : Client_Connection_List) {
            if (user->getSocket() == socket) {
                index = Client_Connection_List.indexOf(user);
                qDebug() << "Disconnected user id" << Client_Connection_List.at(index)->getUserID();
            }
        }
        if (index != -1) {
            QString Client = "Client : " + QString::number(socket->socketDescriptor())
                             + " Disconnected From The Server";
            Client_Connection_List.removeAt(index);
            ui->comboBox_Client_List->removeItem(index);
            ui->textEdit_Client_Messages->append(Client);
            socket->deleteLater();
        }
    }
}

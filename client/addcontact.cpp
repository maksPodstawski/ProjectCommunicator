#include "addcontact.h"
#include "ui_addcontact.h"

AddContact::AddContact(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddContact)
{
    ui->setupUi(this);
    this->setWindowTitle("MatiMax - Adding a new contact");
    QIcon icon("./img/logo.png");
    this->setWindowIcon(icon);
}

AddContact::~AddContact()
{
    delete ui;
}

QString AddContact::getContactName()
{
    return ui->lineEdit_ContactName->text();
}

QString AddContact::getContactIP()
{
    return ui->lineEdit_contactIP->text();
}

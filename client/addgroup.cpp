#include "addgroup.h"
#include "ui_addgroup.h"

addGroup::addGroup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addGroup)
{
    ui->setupUi(this);
    this->setWindowTitle("MatiMax - Adding a new group");
    QIcon icon("./img/logo.png");
    this->setWindowIcon(icon);
}

addGroup::~addGroup()
{
    delete ui;
}

QString addGroup::getGroupName()
{
    return ui->lineEdit_groupName->text();
}

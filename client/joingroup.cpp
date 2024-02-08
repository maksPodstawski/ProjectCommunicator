#include "joingroup.h"
#include "ui_joingroup.h"

joinGroup::joinGroup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::joinGroup)
{
    ui->setupUi(this);
    this->setWindowTitle("MatiMax - Joining a new group");
    QIcon icon("./img/logo.png");
    this->setWindowIcon(icon);
}

joinGroup::~joinGroup()
{
    delete ui;
}

QString joinGroup::getCode()
{
    return ui->lineEdit_groupCode->text();
}

QString joinGroup::getName()
{
    return ui->lineEdit_groupName->text();
}

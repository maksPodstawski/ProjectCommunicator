#include "mainwindow.h"
#include "program.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Program *app)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mainApp(app)
{
    app->setGUI(this);
    ui->setupUi(this);

    connect(app, SIGNAL(wrongIP()), this, SLOT(on_wrongIP()));
    connect(app, SIGNAL(wrongLogin()), this, SLOT(on_wrongLogin()));
    connect(app, SIGNAL(wrongPassword()), this, SLOT(on_wrongPassword()));
    connect(app, SIGNAL(noServerConnection()), this, SLOT(on_noServerConnection()));
    connect(app, SIGNAL(loginFailed(QString)), this, SLOT(on_loginFailed(QString)));
    connect(app, SIGNAL(loginSuccessful()), this, SLOT(on_loginSuccessful()));
    connect(app, SIGNAL(userLoggedOut()), this, SLOT(on_userLoggedOut()));
    QIcon icon("./img/logo.png");
    this->setWindowIcon(icon);
    this->setWindowTitle("MatiMax - log into your account");
    ui->pushButton_backtologin->hide();
    ui->pushButton_register->hide();
    ui->lineEdit_registerIp->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();

    mainApp->SendLoginRequest(login, password);
}

void MainWindow::on_wrongIP()
{
    QMessageBox::warning(this, "Warning", "Wrong IP!");
}

void MainWindow::on_pushButton_register_clicked()
{
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();
    QString ip = ui->lineEdit_registerIp->text();

    if (mainApp->CheckDataIsValid(login, password) && mainApp->CheckIpIsValid(ip))
        mainApp->CreateUserAccount(login, password, ip);
}

void MainWindow::on_wrongLogin()
{
    QMessageBox::warning(this, "Warning", "Wrong Login!");

}

void MainWindow::on_wrongPassword()
{
    QMessageBox::warning(this, "Warning", "Wrong Password!");
}

void MainWindow::on_noServerConnection()
{
    QMessageBox::warning(this, "Warning", "No connection with the server!");
}

void MainWindow::on_loginFailed(const QString &info)
{
    QMessageBox::warning(this, "Warning", info);
}

void MainWindow::on_loginSuccessful()
{
    m_chatWindow = new ChatWindow(mainApp, nullptr);
    m_chatWindow->show();
    ui->lineEdit_login->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_registerIp->clear();
    this->hide();
}

void MainWindow::on_userLoggedOut()
{
    delete m_chatWindow;
    m_chatWindow = nullptr;
    this->show();
}

void MainWindow::on_pushButton_backtologin_clicked()
{
    ui->pushButton_login->show();
    ui->pushButton_backtoregister->show();
    ui->pushButton_backtologin->hide();
    ui->pushButton_register->hide();
    ui->lineEdit_registerIp->hide();
}

void MainWindow::on_pushButton_backtoregister_clicked()
{
    ui->pushButton_login->hide();
    ui->pushButton_backtoregister->hide();
    ui->pushButton_register->show();
    ui->pushButton_backtologin->show();
    ui->lineEdit_registerIp->show();
}

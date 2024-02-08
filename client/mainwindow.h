#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "chatwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Program;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Program *app = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_login_clicked();
    void on_wrongIP();
    void on_pushButton_register_clicked();
    void on_wrongLogin();
    void on_wrongPassword();
    void on_noServerConnection();
    void on_loginFailed(const QString &info);
    void on_loginSuccessful();
    void on_userLoggedOut();

    void on_pushButton_backtologin_clicked();

    void on_pushButton_backtoregister_clicked();

private:
    Ui::MainWindow *ui;
    Program *mainApp = nullptr;
    ChatWindow *m_chatWindow;
};
#endif // MAINWINDOW_H

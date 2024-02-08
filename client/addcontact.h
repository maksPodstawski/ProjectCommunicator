#ifndef ADDCONTACT_H
#define ADDCONTACT_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AddContact;
}

class AddContact : public QDialog
{
    Q_OBJECT

public:
    explicit AddContact(QWidget *parent = nullptr);
    ~AddContact();
    QString getContactName();
    QString getContactIP();

private:
    Ui::AddContact *ui;
};

#endif // ADDCONTACT_H

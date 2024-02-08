#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QDialog>

namespace Ui {
class addGroup;
}

class addGroup : public QDialog
{
    Q_OBJECT

public:
    explicit addGroup(QWidget *parent = nullptr);
    ~addGroup();
    QString getGroupName();

private:
    Ui::addGroup *ui;
};

#endif // ADDGROUP_H

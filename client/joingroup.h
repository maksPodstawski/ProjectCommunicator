#ifndef JOINGROUP_H
#define JOINGROUP_H

#include <QDialog>

namespace Ui {
class joinGroup;
}

class joinGroup : public QDialog
{
    Q_OBJECT

public:
    explicit joinGroup(QWidget *parent = nullptr);
    ~joinGroup();
    QString getCode();
    QString getName();

private:
    Ui::joinGroup *ui;
};

#endif // JOINGROUP_H

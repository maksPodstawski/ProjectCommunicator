#ifndef GROUP_H
#define GROUP_H

#include <QString>

class Group
{
    QString groupName;
    QString groupCode;

public:
    Group();
    Group(const QString name, const QString code);
    QString getGroupName() { return groupName; }
    QString getGroupCode() { return groupCode; }
};

#endif // GROUP_H

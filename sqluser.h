#ifndef SQLUSER_H
#define SQLUSER_H

#include <QObject>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QVector>
#include <QPair>

#include "dbmanager.h"
#include "user.h"

class User;

class SqlUser : public QObject
{
    Q_OBJECT
public:
    explicit SqlUser(QObject *parent = nullptr);
    static QString getNextId();

    bool createUser();
    bool isCredentialsCorrect();
    bool readUser();
    bool updateUser();
    bool deleteUser();

    int getId();
    void setId(int value);

    QString getUsername();
    void setUsername(QString value);

    QString getPassword();
    void setPassword(QString value);

    QDateTime getOccupied();
    void setOccupied(QDateTime value);

    QDateTime getLastActivity();
    void setLastActivity(QDateTime value);

    void userToSqlUserConverter(User &user);

private:
    QString  _username {}, _password {};
    int _id {};
    QDateTime _occupied {}, _last_activity{};

    //TODO: Make field keeping avatar image.

};

#endif // SQLUSER_H

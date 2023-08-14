#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVector>
#include <QPair>

//#include "sqluser.h"

Q_GLOBAL_STATIC(QString, DATABASE_NAME, "chat.db");
Q_GLOBAL_STATIC(QString, CONTACTS_TABLE_NAME, "Contacts");
Q_GLOBAL_STATIC(QString, USERS_TABLE_NAME, "Users");
Q_GLOBAL_STATIC(QString, ID_COLUMN_NAME, "id");
Q_GLOBAL_STATIC(QString, USERNAME_COLUMN_NAME, "username");
Q_GLOBAL_STATIC(QString, PASSWORD_COLUMN_NAME, "password");
Q_GLOBAL_STATIC(QString, NAME_COLUMN, "name");
Q_GLOBAL_STATIC(QString, CONVERSATION_TABLE_NAME, "Conversations");
Q_GLOBAL_STATIC(QString, AUTHOR_COLUMN, "author");
Q_GLOBAL_STATIC(QString, RECIPIENT_COLUMN, "recipient");
Q_GLOBAL_STATIC(QString, TIME_COLUMN, "timestamp");
Q_GLOBAL_STATIC(QString, MESSAGE_COLUMN, "message");

class DbManager : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase _database;
    void CreateTables();
    void CreateContactsTable();
    void CreateConversationTable();
    void CreateUsersTable();

public:
    DbManager(QObject *parent = nullptr);
    static bool create(QString table, QVector<QPair<QString, QString>> args);
    static bool read(QString table, QVector<QPair<QString, QString*>> args);
};

#endif // DBMANAGER_H

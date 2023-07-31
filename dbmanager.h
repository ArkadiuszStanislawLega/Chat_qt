#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

Q_GLOBAL_STATIC(QString, DATABASE_NAME, "chat.db");
Q_GLOBAL_STATIC(QString, CONTACTS_TABLE_NAME, "Contacts");
Q_GLOBAL_STATIC(QString, NAME_COLUMN, "name");
Q_GLOBAL_STATIC(QString, CONVERSATION_TABLE_NAME, "Conversations");
Q_GLOBAL_STATIC(QString, AUTHOR_COLUMN, "author");
Q_GLOBAL_STATIC(QString, RECIPIENT_COLUMN, "recipient");
Q_GLOBAL_STATIC(QString, TIME_COLUMN, "timestamp");
Q_GLOBAL_STATIC(QString, MESSAGE_COLUMN, "message");
Q_GLOBAL_STATIC(QString, CREATE_TABLE, "CREATE TABLE IF NOT EXISTS");
Q_GLOBAL_STATIC(QString, TEXT_NO_NULL, "TEXT NOT NULL");
Q_GLOBAL_STATIC(QString, PRIMARY_KEY, "PRIMARY KEY");

class DbManager : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase _database;
    void CreateTables();
    void CreateContactsTable();
    void CreateConversationTable();

public:
    DbManager(QObject *parent = nullptr);
};

#endif // DBMANAGER_H

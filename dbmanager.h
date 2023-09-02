#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QDebug>
#include <QObject>
#include <QPair>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVector>

// #include "sqluser.h"

Q_GLOBAL_STATIC(QString, DATABASE_NAME, "chat.db");
Q_GLOBAL_STATIC(QString, CONTACTS_TABLE_NAME, "Contacts");
Q_GLOBAL_STATIC(QString, USERS_TABLE_NAME, "Users");
Q_GLOBAL_STATIC(QString, MESSAGES_TABLE_NAME, "Messages");
Q_GLOBAL_STATIC(QString, USERS_CONTACT_TABLE_NAME, "Users_contacts");

Q_GLOBAL_STATIC(QString, ID_COLUMN_NAME, "id");
Q_GLOBAL_STATIC(QString, ID_FIRST_USER_COLUMN_NAME, "first_user_id");
Q_GLOBAL_STATIC(QString, ID_SECOND_USER_COLUMN_NAME, "second_user_id");
Q_GLOBAL_STATIC(QString, CREATE_TIMESTAMP_COLUMN_NAME, "created_timestamp");
Q_GLOBAL_STATIC(QString, USERNAME_COLUMN_NAME, "username");
Q_GLOBAL_STATIC(QString, PASSWORD_COLUMN_NAME, "password");
Q_GLOBAL_STATIC(QString, SENT_TIMESTAMP_COLUMN_NAME, "sent_timestamp");
Q_GLOBAL_STATIC(QString, CONTACT_ID_COLUMN_NAME, "contact_id");
Q_GLOBAL_STATIC(QString, AUTHOR_ID_COLUMN_NAME, "author_id");
Q_GLOBAL_STATIC(QString, USER_ID_COLUMN_NAME, "user_id");
Q_GLOBAL_STATIC(QString, TEXT_COLUMN_NAME, "text");


class DbManager : public QObject {
  Q_OBJECT
private:
  QSqlDatabase _database;
  void CreateTables();
  void CreateContactsTable();
  void CreateMessagesTable();
  void CreateUsersTable();
  void CreateUsersContactTable();
  bool ExecuteQuery(QSqlQuery &);

public:
  DbManager(QObject *parent = nullptr);
};

#endif // DBMANAGER_H

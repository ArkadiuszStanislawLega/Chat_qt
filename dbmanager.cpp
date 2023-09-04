#include "dbmanager.h"
DbManager::DbManager(QObject *parent) : QObject(parent) {
  this->_database = QSqlDatabase::addDatabase("QSQLITE");
  this->_database.setDatabaseName(*DATABASE_NAME);

  if (!this->_database.open()) {
    qDebug() << "Error during connecting to databse.";
  } else {
    qDebug() << "Db connection is ok.";
    this->CreateTables();
  }
}

void DbManager::CreateTables() {
  this->CreateContactsTable();
  this->CreateMessagesTable();
  this->CreateUsersTable();
  this->CreateUsersContactTable();
}

/*
 * CREATE TABLE IF NOT EXISTS Contacts (
id INTEGER PRIMARY KEY AUTOINCREMENT,
created_timestamp datetime NOT NULL);
*/
void DbManager::CreateContactsTable() {
  QSqlQuery query;

  query.prepare(
      "CREATE TABLE IF NOT EXISTS " + *CONTACTS_TABLE_NAME + " (" +
      *ID_COLUMN_NAME + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
      *CREATE_TIMESTAMP_COLUMN_NAME + " DATETIME NOT NULL);");

  this->ExecuteQuery(query);
}

//TODO: Change table conversation to messages.
/*CREATE TABLE "Messages" (
        "id" 			INTEGER PRIMARY KEY,
        "contact_id"		INTEGER NOT NULL,
        "author_id"		INTEGER NOT NULL,
        "text"			TEXT NOT NULL,
        "sent_timestamp"	datetime NOT NULL,
        FOREIGN KEY("author_id") REFERENCES "Users"("id") ON DELETE CASCADE,
        FOREIGN KEY("contact_id") REFERENCES "Contacts"("id") ON DELETE CASCADE
);*/

void DbManager::CreateMessagesTable() {
  QSqlQuery query;

  query.prepare(
      "CREATE TABLE IF NOT EXISTS '" + *MESSAGES_TABLE_NAME + "' (" +
      *ID_COLUMN_NAME + " INTEGER PRIMARY KEY," + *CONTACT_ID_COLUMN_NAME +
      " INTEGER NOT NULL, " + *AUTHOR_ID_COLUMN_NAME + " INTEGER NOT NULL, " +
      *TEXT_COLUMN_NAME + " TEXT NOT NULL, " + *SENT_TIMESTAMP_COLUMN_NAME +
      " DATETIME NOT NULL, " + "FOREIGN KEY(" + *AUTHOR_ID_COLUMN_NAME +
      ") REFERENCES " + *USERS_TABLE_NAME + "(" + *ID_COLUMN_NAME +
      ") ON DELETE CASCADE, " + "FOREIGN KEY(" + *CONTACT_ID_COLUMN_NAME +
      ") REFERENCES " + *CONTACTS_TABLE_NAME + "(" + *ID_COLUMN_NAME +
      ") ON DELETE CASCADE );");
  this->ExecuteQuery(query);
}

/*  query.prepare("CREATE TABLE IF NOT EXISTS '" + *USERS_TABLE_NAME + "' (" +
                "'" + *ID_COLUMN_NAME + "' INTEGER NOT NULL UNIQUE, "
                "'" + *USERNAME_COLUMN_NAME + "' TEXT, "
                "'" + *PASSWORD_COLUMN_NAME + "' TEXT NOT NULL); "
                ); */
void DbManager::CreateUsersTable() {
  QSqlQuery query;
  query.prepare("CREATE TABLE IF NOT EXISTS '" + *USERS_TABLE_NAME + "' (" +
                "'" + *ID_COLUMN_NAME +
                "' INTEGER PRIMARY KEY AUTOINCREMENT, "
                "'" +
                *USERNAME_COLUMN_NAME +
                "' TEXT UNIQUE, "
                "'" +
                *PASSWORD_COLUMN_NAME + "' TEXT NOT NULL); ");
  this->ExecuteQuery(query);
}

/*CREATE TABLE IF NOT EXISTS Users_contacts(
id INTEGER PRIMARY KEY AUTOINCREMENT,
contact_id INTEGER NOT NULL,
user_id INTEGER NOT NULL,
FOREIGN KEY(contact_id) REFERENCES Contacts(id) ON DELETE CASCADE,
FOREIGN KEY(user_id) REFERENCES Users(id) ON DELETE CASCADE
);*/
void DbManager::CreateUsersContactTable() {
  QSqlQuery query;
  query.prepare("CREATE TABLE IF NOT EXISTS " + *USERS_CONTACT_TABLE_NAME +
                "(" + *ID_COLUMN_NAME + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                *CONTACT_ID_COLUMN_NAME + " INTEGER NOT NULL," +
                *USER_ID_COLUMN_NAME + " INTEGER NOT NULL, " + "FOREIGN KEY (" +
                *CONTACT_ID_COLUMN_NAME + ") REFERENCES " +
                *CONTACTS_TABLE_NAME + "(" + *ID_COLUMN_NAME +
                ") ON DELETE CASCADE, " + "FOREIGN KEY (" +
                *USER_ID_COLUMN_NAME + ") REFERENCES " + *USERS_TABLE_NAME +
                "(" + *ID_COLUMN_NAME + ") ON DELETE CASCADE );");
  this->ExecuteQuery(query);
}

bool DbManager::ExecuteQuery(QSqlQuery &query) {
  if (!query.exec()) {
    qFatal("Failed to query 'create table' database: %s, %s",
           qPrintable(query.lastError().text()), qPrintable(query.lastQuery()));
  }
  return true;
}



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

//TODO: Make Contacts new
/*CREATE TABLE "Contacts" (
        "id"			INTEGER  PRIMARY KEY AUTOINCREMENT,
        "first_user"		INTEGER NOT NULL,
        "second_user"		INTEGER NOT NULL,
        "create_timestamp"	datetime NOT NULL,
        FOREIGN KEY(first_user) REFERENCES Users(id) ON DELETE CASCADE,
        FOREIGN KEY(second_user) REFERENCES Users(id) ON DELETE CASCADE
);*/

void DbManager::CreateTables() {
  this->CreateContactsTable();
  this->CreateConversationTable();
  this->CreateUsersTable();
}
void DbManager::CreateContactsTable() {
  QSqlQuery query;

  query.prepare(
      "CREATE TABLE IF NOT EXISTS " + *CONTACTS_TABLE_NAME + " (" +
      *ID_COLUMN_NAME + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
      *ID_FIRST_USER_COLUMN_NAME + " INTEGER NOT NULL, " +
      *ID_SECOND_USER_COLUMN_NAME + " INTEGER NOT NULL, " +
      *CREATE_TIMESTAMP_COLUMN_NAME + " DATETIME NOT NULL, " + "FOREIGN KEY(" +
      *ID_FIRST_USER_COLUMN_NAME + ") REFERENCES " + *USERS_TABLE_NAME + "(" +
      *ID_COLUMN_NAME + ") ON DELETE CASCADE, " + "FOREIGN KEY(" +
      *ID_SECOND_USER_COLUMN_NAME + ") REFERENCES " + *USERS_TABLE_NAME + "(" +
      *ID_COLUMN_NAME + ") ON DELETE CASCADE );"
  );

  if (!query.exec()) {
    qFatal("Failed to query 'create Contacts table' database: %s",
           qPrintable(query.lastError().text()));
  }
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

void DbManager::CreateConversationTable() {
  QSqlQuery query;

  query.prepare("CREATE TABLE IF NOT EXISTS '" + *CONVERSATION_TABLE_NAME +
                "'(" + "'" + *AUTHOR_COLUMN + "' TEXT NOT NULL, "
                "'" + *RECIPIENT_COLUMN + "' TEXT NOT NULL, "
                "'" + *TIME_COLUMN + "' TEXT NOT NULL, "
                "'" + *MESSAGE_COLUMN + "' TEXT NOT NULL, "
                "FOREIGN KEY('" + *AUTHOR_COLUMN + "') REFERENCES " + *CONTACTS_TABLE_NAME + "(" + *NAME_COLUMN + "),"
                "FOREIGN KEY('" + *RECIPIENT_COLUMN + "') REFERENCES " + *CONTACTS_TABLE_NAME + "(" + *NAME_COLUMN + "));");
  if (!query.exec()) {
    qFatal("Failed to query 'create converstation table'database: %s",
           qPrintable(query.lastError().text()));
  }
}

/*  query.prepare("CREATE TABLE IF NOT EXISTS '" + *USERS_TABLE_NAME + "' (" +
                "'" + *ID_COLUMN_NAME + "' INTEGER NOT NULL UNIQUE, "
                "'" + *USERNAME_COLUMN_NAME + "' TEXT, "
                "'" + *PASSWORD_COLUMN_NAME + "' TEXT NOT NULL); "
                ); */
void DbManager::CreateUsersTable() {
  QSqlQuery query;
  query.prepare("CREATE TABLE IF NOT EXISTS '" + *USERS_TABLE_NAME + "' (" +
                "'" + *ID_COLUMN_NAME + "' INTEGER PRIMARY KEY AUTOINCREMENT, "
                "'" + *USERNAME_COLUMN_NAME + "' TEXT UNIQUE, "
                "'" + *PASSWORD_COLUMN_NAME + "' TEXT NOT NULL); "
                );
  if (!query.exec()) {
    qFatal("Failed to query 'create users table' database: %s, %s",
           qPrintable(query.lastError().text()), qPrintable(query.lastQuery()));
  }
}

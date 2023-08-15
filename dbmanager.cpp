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
  this->CreateConversationTable();
  this->CreateUsersTable();
}
void DbManager::CreateContactsTable() {
  QSqlQuery query;
  query.prepare("CREATE TABLE IF NOT EXISTS '" + *CONTACTS_TABLE_NAME +
                "' ("
                "'" +
                *NAME_COLUMN + "' TEXT NOT NULL, PRIMARY KEY(" + *NAME_COLUMN +
                "))");
  if (!query.exec()) {
    qFatal("Failed to query 'create Contacts table' database: %s",
           qPrintable(query.lastError().text()));
  }
}
void DbManager::CreateConversationTable() {
  QSqlQuery query;

  query.prepare("CREATE TABLE IF NOT EXISTS '" + *CONVERSATION_TABLE_NAME +
                "'(" + "'" + *AUTHOR_COLUMN +
                "' TEXT NOT NULL, "
                "'" +
                *RECIPIENT_COLUMN +
                "' TEXT NOT NULL, "
                "'" +
                *TIME_COLUMN +
                "' TEXT NOT NULL, "
                "'" +
                *MESSAGE_COLUMN +
                "' TEXT NOT NULL, "
                "FOREIGN KEY('" +
                *AUTHOR_COLUMN + "') REFERENCES " + *CONTACTS_TABLE_NAME + "(" +
                *NAME_COLUMN +
                "),"
                "FOREIGN KEY('" +
                *RECIPIENT_COLUMN + "') REFERENCES " + *CONTACTS_TABLE_NAME +
                "(" + *NAME_COLUMN + "));");
  if (!query.exec()) {
    qFatal("Failed to query 'create converstation table'database: %s",
           qPrintable(query.lastError().text()));
  }
}
void DbManager::CreateUsersTable() {
  QSqlQuery query;
  query.prepare("CREATE TABLE IF NOT EXISTS '" + *USERS_TABLE_NAME + "' (" +
                "'" + *ID_COLUMN_NAME +
                "' INTEGER NOT NULL UNIQUE, "
                "'" +
                *USERNAME_COLUMN_NAME +
                "' TEXT, "
                "'" +
                *PASSWORD_COLUMN_NAME + "' TEXT NOT NULL); ");
  if (!query.exec()) {
    qFatal("Failed to query 'create users table' database: %s",
           qPrintable(query.lastError().text()));
  }
}

/*!
 * \brief DbManager::create Creates the values given in args in the database in
 * the table with the name given in the function argument.
 * \param table name of the table in database
 * \param args First of pair should be the name of column name in database,
 * second is value.
 * \return True if the table name and values are properly inserted into the
 * database.
 */
bool DbManager::create(QString table, QVector<QPair<QString, QString>> args) {
  if (table.isEmpty())
    return false;
  if (args.isEmpty())
    return false;

  QString cmd = "INSERT INTO " + table, properties{"("}, values{" VALUES("};

  for (int i = 0; i < args.size(); i++) {
    properties += args[i].first;
    values += ":" + args[i].first;

    if (i < args.size() - 1) {
      properties += ",";
      values += ",";
    } else {
      properties += ")";
      values += ")";
    }
  }

  cmd += properties + values + ";";

  QSqlQuery query;
  query.prepare(cmd);

  for (const QPair<QString, QString> &pair : args)
    query.bindValue(":" + pair.first, pair.second);

  if (query.exec())
    return true;
  else {
    qDebug() << query.lastError().text();
    return false;
  }
}
/*!
 * \brief DbManager::read Retrieves the given values in args from the table
 * named in the function argument.
 * \param table name of table in Database
 * \param args First arg must be id. First of pair should be the name of column
 * name in database, second is value.
 * \return true if id is correct and values are readed from Dtabase
 */
bool DbManager::read(QString table, QVector<QPair<QString, QString *>> args) {
  if (table.isEmpty())
    return false;
  if (args.empty())
    return false;

  QSqlQuery query;
  query.prepare("SELECT * FROM " + table + " WHERE id = :id;");
  query.bindValue(":id", *args.at(0).second);

  qDebug() << query.lastQuery();
  if (query.exec()) {
    while (query.next()) {
      QVector<int> columns(args.size());

      for (int i = 0; i < args.size(); i++) {
        columns[i] = query.record().indexOf(args[i].first);
        *args[i].second = query.value(columns[i]).toString();
        qDebug() << args[i].first << *args[i].second;
      }

    }
    return true;
  } else
    qDebug() << query.lastQuery() << query.lastError();

  return false;
}

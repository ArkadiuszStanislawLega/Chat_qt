#include "sqlcontact.h"

SqlContact::SqlContact(QObject *parent) : QObject{parent} {
  this->_id = 0;
  this->_first_user_id = 0;
  this->_second_user_id = 0;
  this->_created_timestamp = QDateTime();
}

bool SqlContact::createUserContact(int &user_id) {
  QSqlQuery query;
  query.prepare("INSERT INTO " + *USERS_CONTACT_TABLE_NAME + " (" +
                *CONTACT_ID_COLUMN_NAME + ", " + *USER_ID_COLUMN_NAME +
                ") VALUES (:" + *CONTACT_ID_COLUMN_NAME +
                ", :" + *USER_ID_COLUMN_NAME + ");");
  query.bindValue(":" + *CONTACT_ID_COLUMN_NAME, this->_id);
  query.bindValue(":" + *USER_ID_COLUMN_NAME, user_id);
  return this->executeQuery(query);
}

bool SqlContact::connectUsersWithContact(int first_contact,
                                         int second_contact) {
  QDateTime current_time = QDateTime::currentDateTime();
  if (!this->createContact(current_time))
    return false;

  this->getLastCreatedContactId(current_time);
  if (this->_id <= 0)
    return false;
  if (!this->createUserContact(first_contact) ||
      !this->createUserContact(second_contact)) {
    this->deleteContact();
    return false;
  }
  return true;
}

bool SqlContact::getLastCreatedContactId(const QDateTime &timestamp) {
  QSqlQuery query;
  query.prepare("SELECT * FROM " + *CONTACTS_TABLE_NAME + " WHERE " +
                *CREATE_TIMESTAMP_COLUMN_NAME +
                " = :" + *CREATE_TIMESTAMP_COLUMN_NAME + ";");
  query.bindValue(":" + *CREATE_TIMESTAMP_COLUMN_NAME, timestamp);
  if (!this->executeQuery(query))
    return -1;

  int id_column = query.record().indexOf(*ID_COLUMN_NAME);
  this->_id = query.value(id_column).toInt();

  return true;
}

bool SqlContact::createContact(const QDateTime &timestamp) {
  if (timestamp.isNull())
    return false;

  QSqlQuery query;
  query.prepare("INSERT INTO " + *CONTACTS_TABLE_NAME + "(" +
                *CREATE_TIMESTAMP_COLUMN_NAME +
                ") VALUES (:" + *CREATE_TIMESTAMP_COLUMN_NAME + ");");
  query.bindValue(":" + *CREATE_TIMESTAMP_COLUMN_NAME,
                  this->_created_timestamp);

  return this->executeQuery(query);
}

bool SqlContact::executeQuery(QSqlQuery &query) {
  if (!query.exec()) {
    qDebug() << query.lastError() << query.lastQuery();
    return false;
  }
  return true;
}

bool SqlContact::readContact() {
  QSqlQuery query;
  query.prepare("SELECT * FROM " + *CONTACTS_TABLE_NAME + " WHERE " +
                *ID_FIRST_USER_COLUMN_NAME +
                " = :" + *ID_FIRST_USER_COLUMN_NAME + " AND " +
                *ID_SECOND_USER_COLUMN_NAME +
                " = :" + *ID_SECOND_USER_COLUMN_NAME + ";");

  query.bindValue(":" + *ID_FIRST_USER_COLUMN_NAME, this->_first_user_id);
  query.bindValue(":" + *ID_SECOND_USER_COLUMN_NAME, this->_second_user_id);

  if (!this->executeQuery(query))
    return false;

  while (query.next()) {
    int id_column, create_timestamp_column, id_first_column, id_second_column;

    id_column = query.record().indexOf(*ID_COLUMN_NAME);
    create_timestamp_column =
        query.record().indexOf(*CREATE_TIMESTAMP_COLUMN_NAME);
    id_first_column = query.record().indexOf(*ID_FIRST_USER_COLUMN_NAME);
    id_second_column = query.record().indexOf(*ID_SECOND_USER_COLUMN_NAME);

    this->_id = query.value(id_column).toInt();
    this->_first_user_id = query.value(id_first_column).toInt();
    this->_second_user_id = query.value(id_second_column).toInt();
    this->_created_timestamp =
        query.value(create_timestamp_column).toDateTime();
    return true;
  }

  return false;
}

bool SqlContact::updateContact() { return false; }
bool SqlContact::deleteContact() {
  this->readContact();

  QSqlQuery query;
  query.prepare("DELETE FROM " + *CONTACTS_TABLE_NAME + " WHERE " +
                *ID_COLUMN_NAME + " = :" + *ID_COLUMN_NAME + ";");

  query.bindValue(":" + *ID_COLUMN_NAME, this->_id);
  return this->executeQuery(query);
}

QVector<Contact *> SqlContact::get_user_contacts() {
  QSqlQuery query;
  query.prepare(
      "SELECT " + *CONTACTS_TABLE_NAME + "." + *ID_COLUMN_NAME + ", " +
      *ID_SECOND_USER_COLUMN_NAME + ", " + *CREATE_TIMESTAMP_COLUMN_NAME +
      ", " + *USERNAME_COLUMN_NAME + " FROM " + *CONTACTS_TABLE_NAME +
      " INNER JOIN " + *USERS_TABLE_NAME + " ON " + *USERS_TABLE_NAME + "." +
      *ID_COLUMN_NAME + " = " + *CONTACTS_TABLE_NAME + "." +
      *ID_SECOND_USER_COLUMN_NAME + " WHERE " + *ID_FIRST_USER_COLUMN_NAME +
      " = :" + *ID_FIRST_USER_COLUMN_NAME + ";");

  query.bindValue(":" + *ID_FIRST_USER_COLUMN_NAME, this->_first_user_id);

  if (!this->executeQuery(query))
    return {};

  QVector<Contact *> contacts;
  while (query.next()) {
    int id_column{}, id_user_column{}, create_datestamp_column{},
        username_column{};

    id_column = query.record().indexOf(*ID_COLUMN_NAME);
    id_user_column = query.record().indexOf(*ID_SECOND_USER_COLUMN_NAME);
    create_datestamp_column =
        query.record().indexOf(*CREATE_TIMESTAMP_COLUMN_NAME);
    username_column = query.record().indexOf(*USERNAME_COLUMN_NAME);

    int id = query.value(id_column).toInt();
    QDateTime date = query.value(create_datestamp_column).toDateTime();
    User *user = new User(this);
    user->setDbId(query.value(id_user_column).toString());
    user->setUsername(query.value(username_column).toString());

    contacts.push_back(new Contact(id, user, date, this->_first_user_id, this));
  }
  return contacts;
}

QDateTime SqlContact::getCreatedTimestamp() { return this->_created_timestamp; }
void SqlContact::setCreatedTimestamp(QDateTime value) {
  this->_created_timestamp = value;
}

int SqlContact::getFirstUserId() { return _first_user_id; }
void SqlContact::setFirstUserId(int value) { this->_first_user_id = value; }

int SqlContact::getSecondUserId() const { return _second_user_id; }
void SqlContact::setSecondUserId(int value) { this->_second_user_id = value; }

int SqlContact::getId() const { return _id; }

void SqlContact::setId(int newId) { _id = newId; }

QList<Message *> SqlContact::getMessages() {
  SqlMessage *sql = new SqlMessage(this);
  sql->setContactId(this->_id);
  sql->setAuthorId(this->_first_user_id);
  sql->setReceiverId(this->_second_user_id);

  return sql->readMessages();
}

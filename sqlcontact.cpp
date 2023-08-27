#include "sqlcontact.h"

SqlContact::SqlContact(QObject *parent) : QObject{parent} {
  this->_id = 0;
  this->_contact_id = 0;
  this->_first_user_id = 0;
  this->_second_user_id = 0;
  this->_created_timestamp = QDateTime();
}

bool SqlContact::createContact() {
  if (this->readContact())
    return false;

  QSqlQuery query;
  query.prepare("INSERT INTO " + *CONTACTS_TABLE_NAME + "(" +
                *ID_FIRST_USER_COLUMN_NAME + ", " +
                *ID_SECOND_USER_COLUMN_NAME + ", " +
                *CREATE_TIMESTAMP_COLUMN_NAME +
                ") VALUES (:" + *ID_FIRST_USER_COLUMN_NAME +
                ",:" + *ID_SECOND_USER_COLUMN_NAME +
                ",:" + *CREATE_TIMESTAMP_COLUMN_NAME + ");");
  query.bindValue(":" + *ID_FIRST_USER_COLUMN_NAME, this->_first_user_id);
  query.bindValue(":" + *ID_SECOND_USER_COLUMN_NAME, this->_second_user_id);
  query.bindValue(":" + *CREATE_TIMESTAMP_COLUMN_NAME,
                  this->_created_timestamp);

  return this->executeQuery(query) ? isAddingContactComplited() : false;
}

bool SqlContact::isAddingContactComplited() {
  QSqlQuery query;
  query.prepare(
      "SELECT * FROM " + *CONTACTS_TABLE_NAME + " WHERE " +
      *CREATE_TIMESTAMP_COLUMN_NAME + " = :" + *CREATE_TIMESTAMP_COLUMN_NAME +
      " AND " + *ID_FIRST_USER_COLUMN_NAME +
      " = :" + *ID_FIRST_USER_COLUMN_NAME + " AND " +
      *ID_SECOND_USER_COLUMN_NAME + " = :" + *ID_SECOND_USER_COLUMN_NAME + ";");

  query.bindValue(":" + *CREATE_TIMESTAMP_COLUMN_NAME,
                  this->_created_timestamp);
  query.bindValue(":" + *ID_FIRST_USER_COLUMN_NAME, this->_first_user_id);
  query.bindValue(":" + *ID_SECOND_USER_COLUMN_NAME, this->_second_user_id);

  if (!this->executeQuery(query))
    return false;

  while (query.next()) {
    int create_timestamp_column, id_first_column, id_second_column;
    int first_id, second_id;
    QDateTime create_timestamp;

    create_timestamp_column =
        query.record().indexOf(*CREATE_TIMESTAMP_COLUMN_NAME);
    id_first_column = query.record().indexOf(*ID_FIRST_USER_COLUMN_NAME);
    id_second_column = query.record().indexOf(*ID_SECOND_USER_COLUMN_NAME);

    first_id = query.value(id_first_column).toInt();
    second_id = query.value(id_second_column).toInt();
    create_timestamp = query.value(create_timestamp_column).toDateTime();

    return first_id == this->_first_user_id &&
           second_id == this->_second_user_id &&
           create_timestamp == this->_created_timestamp;
  }

  return false;
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
      "SELECT " + *ID_SECOND_USER_COLUMN_NAME + ", " +
      *CREATE_TIMESTAMP_COLUMN_NAME + ", " + *USERNAME_COLUMN_NAME + " FROM " +
      *CONTACTS_TABLE_NAME + " INNER JOIN " + *USERS_TABLE_NAME + " ON " +
      *USERS_TABLE_NAME + "." + *ID_COLUMN_NAME + " = " + *CONTACTS_TABLE_NAME +
      "." + *ID_SECOND_USER_COLUMN_NAME + " WHERE " +
      *ID_FIRST_USER_COLUMN_NAME + " = :" + *ID_FIRST_USER_COLUMN_NAME + ";");

  query.bindValue(":" + *ID_FIRST_USER_COLUMN_NAME, this->_first_user_id);

  if (!this->executeQuery(query))
    return {};

  QVector<Contact *> contacts;
  while (query.next()) {
    int id_user_column{}, create_datestamp_column{}, username_column{};
    id_user_column = query.record().indexOf(*ID_SECOND_USER_COLUMN_NAME);
    create_datestamp_column =
        query.record().indexOf(*CREATE_TIMESTAMP_COLUMN_NAME);
    username_column = query.record().indexOf(*USERNAME_COLUMN_NAME);

    QDateTime date = query.value(create_datestamp_column).toDateTime();
    User *user = new User(this);
    user->setDbId(query.value(id_user_column).toString());
    user->setUsername(query.value(username_column).toString());

    contacts.push_back(new Contact(this->_id, user, date, this));
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

int SqlContact::getContactId() const { return this->_contact_id; }
void SqlContact::setContactId(int value) { this->_contact_id = value; }

int SqlContact::getId() const { return _id; }

void SqlContact::setId(int newId) { _id = newId; }

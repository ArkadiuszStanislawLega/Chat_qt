#include "sqlcontact.h"

SqlContact::SqlContact(QObject *parent) : QObject{parent} {
  this->_contact_id = 0;
  this->_first_user_id = 0;
  this->_second_user_id = 0;
  QString _username = "";
  QDateTime _created = QDateTime();
}

bool SqlContact::createContact() {
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

  if (!query.exec()) {
    qDebug() << query.lastError() << query.lastQuery();
    return false;
  }

  return isAddingContactComplited();
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

  if (!query.exec()) {
    qDebug() << query.lastError() << query.lastQuery();
    return false;
  }

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

bool SqlContact::readContact() {
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

  if (!query.exec()) {
    qDebug() << query.lastError() << query.lastQuery();
    return false;
  }

  while (query.next()) {
    int create_timestamp_column, id_first_column, id_second_column;

    create_timestamp_column =
        query.record().indexOf(*CREATE_TIMESTAMP_COLUMN_NAME);
    id_first_column = query.record().indexOf(*ID_FIRST_USER_COLUMN_NAME);
    id_second_column = query.record().indexOf(*ID_SECOND_USER_COLUMN_NAME);

    this->_first_user_id = query.value(id_first_column).toInt();
    this->_second_user_id = query.value(id_second_column).toInt();
    this->_created_timestamp =
        query.value(create_timestamp_column).toDateTime();
    return true;
  }

  return false;
}

bool SqlContact::updateContact() { return false; }
bool SqlContact::deleteContact() { return false; }

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

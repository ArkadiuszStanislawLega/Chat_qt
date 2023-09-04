#include "sqlcontact.h"

SqlContact::SqlContact(QObject *parent) : QObject{parent} {
  this->_id = 0;
  this->_user_id = 0;
  this->_created_timestamp = QDateTime();
}

bool SqlContact::createUserContact(int &user_id) {
  QSqlQuery query;
  query.prepare("INSERT INTO " + *USERS_CONTACT_TABLE_NAME + " (" + *CONTACT_ID_COLUMN_NAME + ", "
                + *USER_ID_COLUMN_NAME + ") VALUES (:" + *CONTACT_ID_COLUMN_NAME
                + ", :" + *USER_ID_COLUMN_NAME + ");");
  query.bindValue(":" + *CONTACT_ID_COLUMN_NAME, this->_id);
  query.bindValue(":" + *USER_ID_COLUMN_NAME, user_id);
  return this->executeQuery(&query);
}

bool SqlContact::connectUsersWithContact(int first_contact,
                                         int second_contact) {
  QDateTime current_time = QDateTime::currentDateTime();
  if (!this->createContact(current_time))
    return false;

  if (this->_id <= 0)
    return false;
  if (!this->createUserContact(first_contact) ||
      !this->createUserContact(second_contact)) {
    this->deleteContact();
    return false;
  }
  return true;
}

bool SqlContact::createContact(const QDateTime &timestamp) {
  if (timestamp.isNull())
    return false;

  QSqlQuery query;
  query.prepare("INSERT INTO " + *CONTACTS_TABLE_NAME + "(" + *CREATE_TIMESTAMP_COLUMN_NAME
                + ") VALUES (:" + *CREATE_TIMESTAMP_COLUMN_NAME + ");");
  query.bindValue(":" + *CREATE_TIMESTAMP_COLUMN_NAME, this->_created_timestamp);

  if (this->executeQuery(&query)) {
    this->_id = query.lastInsertId().toInt();

    return true;
  }
  return false;
}

bool SqlContact::executeQuery(QSqlQuery *query)
{
  qDebug() << "SqlContact executing: " << query->lastQuery();
  if (!query->exec()) {
    qDebug() << query->lastError() << query->lastQuery();
    return false;
  }
  return true;
}

bool SqlContact::readContact() {
  QSqlQuery query;
  query.prepare(this->selectContactQuery());
  query.bindValue(":" + *CONTACT_ID_COLUMN_NAME, this->_id);

  if (!this->executeQuery(&query))
    return false;

  while (query.next()) {
    return this->getContactFromQuery(&query);
  }

  return false;
}

QString SqlContact::selectContactQuery()
{
  QString contacts_id, created_timestamp, users_contacts_id, users_contacts_user_id, users_username,
      ij_users_contacts_to_contacts, ij_users_to_users_contact, second_select, full_query;

  contacts_id = *CONTACTS_TABLE_NAME + "." + *ID_COLUMN_NAME + " AS " + ALIAS_CONTACT_ID;
  created_timestamp = *CONTACTS_TABLE_NAME + "." + *CREATE_TIMESTAMP_COLUMN_NAME;
  users_contacts_id = *USERS_CONTACT_TABLE_NAME + "." + *ID_COLUMN_NAME + " AS "
                      + ALIAS_USER_CONTACT_ID;
  users_contacts_user_id = *USERS_CONTACT_TABLE_NAME + "." + *USER_ID_COLUMN_NAME;
  users_username = *USERS_TABLE_NAME + "." + *USERNAME_COLUMN_NAME;
  ij_users_contacts_to_contacts = " INNER JOIN " + *USERS_CONTACT_TABLE_NAME + " ON "
                                  + *USERS_CONTACT_TABLE_NAME + "." + *CONTACT_ID_COLUMN_NAME
                                  + " = " + *CONTACTS_TABLE_NAME + "." + *ID_COLUMN_NAME;
  ij_users_to_users_contact = " INNER JOIN " + *USERS_TABLE_NAME + " ON "
                              + *USERS_CONTACT_TABLE_NAME + "." + *USER_ID_COLUMN_NAME + " = "
                              + *USERS_TABLE_NAME + "." + *ID_COLUMN_NAME;
  second_select = " INNER JOIN (SELECT " + *USERS_CONTACT_TABLE_NAME + "." + *CONTACT_ID_COLUMN_NAME
                  + "," + *USERS_CONTACT_TABLE_NAME + "." + *USER_ID_COLUMN_NAME + " FROM "
                  + *USERS_CONTACT_TABLE_NAME + " WHERE " + *USER_ID_COLUMN_NAME
                  + " = :" + *USER_ID_COLUMN_NAME + ")";

  full_query = "SELECT DISTINCT " + contacts_id + ", " + created_timestamp + ", "
               + users_contacts_id + ", " + users_contacts_user_id + ", " + users_username
               + " FROM " + *CONTACTS_TABLE_NAME + ij_users_contacts_to_contacts
               + ij_users_to_users_contact + " WHERE " + *USERS_CONTACT_TABLE_NAME + "."
               + *CONTACT_ID_COLUMN_NAME + " != :" + *ID_COLUMN_NAME + ";";
  return full_query;
}

bool SqlContact::updateContact() { return false; }
bool SqlContact::deleteContact() {
  this->readContact();

  QSqlQuery query;
  query.prepare("DELETE FROM " + *CONTACTS_TABLE_NAME + " WHERE " + *ID_COLUMN_NAME
                + " = :" + *ID_COLUMN_NAME + ";");

  query.bindValue(":" + *ID_COLUMN_NAME, this->_id);
  return this->executeQuery(&query);
}

QVector<Contact *> SqlContact::get_user_contacts() {
  QSqlQuery query;
  query.prepare(this->selectContactsQuery());
  query.bindValue(":" + *USER_ID_COLUMN_NAME, this->_user_id);

  if (!this->executeQuery(&query))
    return {};

  return getContactsFromQuery(&query);
}

/*
SELECT DISTINCT
        Contacts.id as conctact_id,
        Contacts.created_timestamp,
        Users_contacts.id as user_contact_id,
        Users_contacts.user_id,
        Users.username FROM Contacts
INNER JOIN Users_contacts ON Users_contacts.contact_id = Contacts.id
INNER JOIN Users ON Users_contacts.user_id = Users.id
INNER JOIN (SELECT Users_contacts.contact_id, Users_contacts.user_id FROM
Users_contacts WHERE user_id = 34) WHERE Users_contacts.user_id != 34;
*/
QString SqlContact::selectContactsQuery() {
  QString contacts_id, created_timestamp, users_contacts_id, users_contacts_user_id, users_username,
      ij_users_contacts_to_contacts, ij_users_to_users_contact, second_select, full_query;

  contacts_id = *CONTACTS_TABLE_NAME + "." + *ID_COLUMN_NAME + " AS " + ALIAS_CONTACT_ID;
  created_timestamp =
      *CONTACTS_TABLE_NAME + "." + *CREATE_TIMESTAMP_COLUMN_NAME;
  users_contacts_id = *USERS_CONTACT_TABLE_NAME + "." + *ID_COLUMN_NAME + " AS "
                      + ALIAS_USER_CONTACT_ID;
  users_contacts_user_id =
      *USERS_CONTACT_TABLE_NAME + "." + *USER_ID_COLUMN_NAME;
  users_username = *USERS_TABLE_NAME + "." + *USERNAME_COLUMN_NAME;
  ij_users_contacts_to_contacts = " INNER JOIN " + *USERS_CONTACT_TABLE_NAME +
                                  " ON " + *USERS_CONTACT_TABLE_NAME + "." +
                                  *CONTACT_ID_COLUMN_NAME + " = " +
                                  *CONTACTS_TABLE_NAME + "." + *ID_COLUMN_NAME;
  ij_users_to_users_contact = " INNER JOIN " + *USERS_TABLE_NAME + " ON " +
                              *USERS_CONTACT_TABLE_NAME + "." +
                              *USER_ID_COLUMN_NAME + " = " + *USERS_TABLE_NAME +
                              "." + *ID_COLUMN_NAME;
  second_select = " INNER JOIN (SELECT " + *USERS_CONTACT_TABLE_NAME + "." +
                  *CONTACT_ID_COLUMN_NAME + "," + *USERS_CONTACT_TABLE_NAME +
                  "." + *USER_ID_COLUMN_NAME + " FROM " +
                  *USERS_CONTACT_TABLE_NAME + " WHERE " + *USER_ID_COLUMN_NAME +
                  " = :" + *USER_ID_COLUMN_NAME + ")";

  full_query = "SELECT DISTINCT " + contacts_id + ", " + created_timestamp +
               ", " + users_contacts_id + ", " + users_contacts_user_id + ", " +
               users_username + " FROM " + *CONTACTS_TABLE_NAME +
               ij_users_contacts_to_contacts + ij_users_to_users_contact +
               second_select + " WHERE " + *USERS_CONTACT_TABLE_NAME + "." +
               *USER_ID_COLUMN_NAME + " != :" + *USER_ID_COLUMN_NAME + ";";
  return full_query;
}

QVector<Contact *> SqlContact::getContactsFromQuery(QSqlQuery *query)
{
  QVector<Contact *> contacts;
  while (query->next()) {
    contacts.push_back(this->getContactFromQuery(query));
  }
  return contacts;
}

Contact *SqlContact::getContactFromQuery(QSqlQuery *query)
{
  int id_column{}, id_user_column{}, create_datestamp_column{}, username_column{};

  id_column = query->record().indexOf(ALIAS_CONTACT_ID);
  id_user_column = query->record().indexOf(*USER_ID_COLUMN_NAME);
  create_datestamp_column = query->record().indexOf(*CREATE_TIMESTAMP_COLUMN_NAME);
  username_column = query->record().indexOf(*USERNAME_COLUMN_NAME);

  int id = query->value(id_column).toInt();
  QDateTime date = query->value(create_datestamp_column).toDateTime();
  User *user = new User(this);
  user->setDbId(query->value(id_user_column).toString());
  user->setUsername(query->value(username_column).toString());

  return new Contact(id, user, date, this);
}

QDateTime SqlContact::getCreatedTimestamp() { return this->_created_timestamp; }
void SqlContact::setCreatedTimestamp(QDateTime value) {
  this->_created_timestamp = value;
}

int SqlContact::getUserId() { return _user_id; }
void SqlContact::setUserId(int value) { this->_user_id = value; }

int SqlContact::getId() const { return _id; }
void SqlContact::setId(int newId) { _id = newId; }

QList<Message *> SqlContact::getMessages() {
  SqlMessage *sql = new SqlMessage(this);
  sql->setContactId(this->_id);
  return sql->readMessages();
}

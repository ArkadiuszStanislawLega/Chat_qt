#include "user.h"
User::User(QObject *parent) : QObject{parent} {
  this->_id = "1";
  this->_username = "";

         // TODO: Move this to server. Get empty id from server.
  this->_id = SqlUser::getNextId();
}
User::User(QString id, QString username, QVector<Contact> contacts, QObject *parent)
    : QObject{parent} {
  this->_id = id;
  this->_username = username;
  this->_contacts = contacts;
}
QString User::getUsername() { return this->_username; }
QString User::getDbId() { return this->_id; }
QVector<Contact> User::getContacts() {
  // TODO: Make function to connect with db.
  return this->_contacts;
}

void User::setUsername(QString username) {
  this->_username = username;
  qDebug() << "setUsername:" << username;
}
void User::setDbId(QString id) {
  this->_id = id;
  qDebug() << "setId:" << id;
}
void User::sqlUserToUserConverter(SqlUser &user) {
  this->_id = QString::number(user.getId());
  this->_username = user.getUsername();
}

void User::setContacts(QVector<Contact> contacts) {
  this->_contacts = contacts;
}
void User::registerUser(QString *password) { this->addUserToDb(password); }
void User::isUserLogin(QString *password) {
  if (this->auteticateUser(password))
    emit this->isLoginIn();
  else
    emit this->loginInFail();
}

void User::addUserToDb(QString *password) {
  // TODO: Move this to server.
  // TODO: Change insert into to update - after create server.
  SqlUser sql;
  sql.userToSqlUserConverter(*this);
  if (sql.createUser(password)) {
    this->_id = SqlUser::getNextId();
    this->_username = "";

    emit this->createdConfirmed();
  } else
    emit this->createdError();
}
bool User::auteticateUser(QString *password) {
  // TODO: Move this to server.
  SqlUser sql;
  sql.userToSqlUserConverter(*this);
  if (!sql.isCredentialsCorrect(password)) {
    return false;
  }

  if (sql.readUser()) {
    this->sqlUserToUserConverter(sql);
    return true;
  }

  return false;
}

bool User::addContact(Contact &contact) {
  // TODO: Not fully functionall.
  if (contact.create()) {
    this->getContacts();
    emit this->contactsChanged();
    return true;
  }

  return false;
}

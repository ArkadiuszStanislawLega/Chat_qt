#include "user.h"
User::User(QObject *parent) : QObject{parent} {
  this->_id = "1";
  this->_password = "";
  this->_username = "";

  // TODO: Move this to server. Get empty id from server.
  this->_id = SqlUser::getNextId();
}
User::User(QString id, QString username, QString password, QVector<Contact> contacts, QObject *parent)
    : QObject{parent} {
  this->_id = id;
  this->_username = username;
  this->_password = password;
  this->_contacts = contacts;
}
QString User::getPassword() { return this->_password; }
QString User::getUsername() { return this->_username; }
QString User::getDbId() { return this->_id; }
QVector<Contact> User::getContacts() {
  //TODO: Make function to connect with db.
  return this->_contacts;
}

void User::setPassword(QString password) {
  this->_password = QString(
      QCryptographicHash::hash((password.toUtf8()), QCryptographicHash::Md5)
          .toHex());
  qDebug() << "setPassword:" << this->_password;
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
  this->_password = user.getPassword();
}

void User::setContacts(QVector<Contact> contacts) { this->_contacts = contacts; }
void User::registerUser() { this->addUserToDb(); }
void User::isUserLogin() {
  if (this->auteticateUser())
    emit this->isLoginIn();
  else
    emit this->loginInFail();
}

void User::addUserToDb() {
  // TODO: Move this to server.
  // TODO: Change insert into to update - after create server.
  SqlUser sql;
  sql.userToSqlUserConverter(*this);
  if (sql.createUser()) {
    this->_id = SqlUser::getNextId();
    this->_username = "";
    this->_password = "";

    emit this->createdConfirmed();
  } else
    emit this->createdError();
}
bool User::auteticateUser() {
  // TODO: Move this to server.
  SqlUser sql;
  sql.userToSqlUserConverter(*this);
  if (!sql.isCredentialsCorrect()) {
    return false;
  }

  if (sql.readUser()) {
    this->sqlUserToUserConverter(sql);
         qDebug() << "ok";
    return true;
  }
  qDebug() << "not ok";

  return false;
}

bool User::addContact(Contact &contact) {
  if (contact.create()) {
    this->getContacts();
  }

  emit this->contactsChanged();
}


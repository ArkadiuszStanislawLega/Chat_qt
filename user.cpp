#include "user.h"
User::User(QObject *parent) : QObject{parent} {
  this->_id = "1";
  this->_username = "";
}
User::User(QString id, QString username, QVector<Contact *> contacts, QObject *parent)
    : QObject{parent}
{
  this->_id = id;
  this->_username = username;
  this->_contacts = contacts;
}

/*!
 * \brief User::sqlUserToUserConverter converting SqlUser to user - user doesn't have password.
 * \param user Dwonloaded user properties from database.
 */
void User::sqlUserToUserConverter(SqlUser &user) {
  this->_id = QString::number(user.getId());
  this->_username = user.getUsername();
}

void User::addUserToDb(QString password) {
  // TODO: Move this to server.
  // TODO: Change insert into to update - after create server.

  password =
      QCryptographicHash::hash((password.toUtf8()), QCryptographicHash::Md5)
          .toHex();
  SqlUser sql;
  sql.userToSqlUserConverter(*this);
  sql.setPassword(password);

  if (sql.createUser()) {
    this->setDbId(QString::number(sql.getId()));
    emit this->createdConfirmed();
  } else
    emit this->createdError();
}

void User::isUserLogin(QString password) {
  password =
      QCryptographicHash::hash((password.toUtf8()), QCryptographicHash::Md5)
          .toHex();

  if (this->auteticateUser(password))
    emit this->isLoginIn();
  else
    emit this->loginInFail();
}

void User::createContact(QString val) {
  SqlUser *sql = new SqlUser(this);
  sql->setId(this->_id.toInt());

  if(sql->createContact(val.toInt())) {
    emit this->contactCreated();
    emit this->contactsChanged();
  }
  else emit this->failToCreateContact();
  delete(sql);
}

void User::deleteContact(QString userId) {
  if (userId.isEmpty())
    return;

  SqlUser *sql = new SqlUser(this);
  sql->setId(this->_id.toInt());

  if (sql->removeContact(userId.toInt())) {
    emit contactsChanged();
  }
}

bool User::auteticateUser(QString password) {
  if (password.isEmpty())
    return false;

  // TODO: Move this to server.
  SqlUser sql;
  sql.userToSqlUserConverter(*this);

  if (!sql.isCredentialsCorrect(this->_id.toInt(), password)) {
    return false;
  }

  if (sql.readUser()) {
    this->sqlUserToUserConverter(sql);
    return true;
  }

  return false;
}

QString User::getUsername() { return this->_username; }
void User::setUsername(QString username) { this->_username = username; }

QString User::getDbId() { return this->_id; }
void User::setDbId(QString id) {
  this->_id = id;
  emit this->idChanged();
}

QVector<Contact *> User::getContacts() {
  if (this->_id.isEmpty())
	return this->_contacts;

  SqlContact *sql = new SqlContact(this);
  sql->setUserId(this->_id.toInt());

  this->_contacts = sql->getUserContacts();
  return this->_contacts;
}
void User::setContacts(QVector<Contact *> contacts)
{
  this->_contacts = contacts;
}

bool User::sendMessage(int receiverId, QString message) {
  SqlMessage *sql = new SqlMessage(this);
  sql->setAuthorId(this->_id.toInt());
  sql->setSentTimestamp(QDateTime::currentDateTime());
  sql->setText(message);

  if (sql->createMessage()) {
    emit this->messageSended();
    return true;
  }

  emit this->failToSendMessage();
  return false;
}

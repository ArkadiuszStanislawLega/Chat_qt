#include "sqlcontact.h"

SqlContact::SqlContact(QObject *parent) : QObject{parent} {
  this->_contact_id = 0;
  this->_owner_id = 0;
  this->_user_id = 0;
  QString _username = "";
  QDateTime _created = QDateTime();
}

bool SqlContact::createContact() {
  QVector<QPair<QString, QString>> args = {
      {*ID_COLUMN_NAME, QString::number(this->_contact_id)},
      {*ID_OWNER_ID_COLUMN_NAME, QString::number(this->_owner_id)},
      {*ID_USER_ID_COLUMN_NAME, QString::number(this->_user_id)},
      {*USERNAME_COLUMN_NAME, this->_username},
      {*CREATED_DATE_COLUMN_NAME, this->_created.toString()},
  };
  return DbManager::create(*CONTACTS_TABLE_NAME, args);
}

bool SqlContact::readContact() {
  QString username, id_contact, id_owner, id_user, created;
  QVector<QPair<QString, QString *>> args = {
      {*ID_COLUMN_NAME, &id_contact},
      {*ID_OWNER_ID_COLUMN_NAME, &id_owner},
      {*ID_USER_ID_COLUMN_NAME, &id_user},
      {*USERNAME_COLUMN_NAME, &username},
      {*CREATED_DATE_COLUMN_NAME, &created}};
  if (DbManager::read(*CONTACTS_TABLE_NAME, args)) {
    this->setContactId(id_contact.toInt());
    this->setOwnerId(id_owner.toInt());
    this->setUserId(id_user.toInt());
    this->setUsername(username);
    this->setCreated(QDateTime::fromString(created));
    return true;
  }
  return false;
}

bool SqlContact::updateContact() { return false; }

bool SqlContact::deleteContact() { return false; }

int SqlContact::getContactId() { return this->_contact_id; }
void SqlContact::setContactId(int value) { this->_contact_id = value; }
int SqlContact::getOwnerId() { return this->_owner_id; }
void SqlContact::setOwnerId(int value) { this->_owner_id = value; }
int SqlContact::getUserId() { return this->_user_id; }
void SqlContact::setUserId(int value) { this->_user_id = value; }
QString SqlContact::getUsername() { return this->_username; }
void SqlContact::setUsername(QString value) { this->_username = value; }
QDateTime SqlContact::getCreated() { return this->_created; }
void SqlContact::setCreated(QDateTime value) { this->_created = value; }

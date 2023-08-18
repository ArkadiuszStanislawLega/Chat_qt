#include "sqlcontact.h"

SqlContact::SqlContact(QObject *parent) : QObject{parent} {
  this->_contact_id = 0;
  this->_owner_id = 0;
  this->_user_id = 0;
  QString _username = "";
  QDateTime _created = QDateTime();
}

bool SqlContact::createContact() { return false; }

bool SqlContact::readContact() { return false; }

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

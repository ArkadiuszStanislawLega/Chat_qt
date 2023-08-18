#include "contact.h"

Contact::Contact(QObject *parent) : QObject{parent} {
  this->_username = {};
  this->_contact_id = {};
  this->_created = QDateTime();
}

Contact::Contact(QString contact_id, QString owner_id, QString user_id,
                 QString username, QDateTime created, QObject *parent) {
  this->_contact_id = contact_id;
  this->_user_id = user_id;
  this->_owner_id = owner_id;
  this->_username = username;
  this->_created = created;
}

void Contact::setUsername(QString value) {
  this->_username = value;
  emit this->usernameChanged();
}
QString Contact::getUsername() { return this->_username; }

void Contact::setContactId(QString value) {
  this->_contact_id = value;
  emit this->contactIdChanged();
}
QString Contact::getContactId() { return this->_contact_id; }

void Contact::setOnwerId(QString value) {
  this->_owner_id = value;
  emit this->ownerIdChanged();
}
QString Contact::getOwnerId() { return this->_owner_id; }

QString Contact::getUserId() { return this->_user_id; }
void Contact::setUserId(QString value) {
  this->_user_id = value;
  emit this->userIdChanged();
}

QDateTime Contact::getCreated() { return this->_created; }

void Contact::setCreated(QDateTime value) {
  this->_created = value;
  emit this->created();
}

void Contact::remove() {
  // TODO: make remove from db;
  emit this->removed();
}

void Contact::create() { SqlUser *user; }

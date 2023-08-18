#include "contact.h"

Contact::Contact(QObject *parent) : QObject{parent} {
  this->_owner_id = {};
  this->_user_id = {};
  this->_username = {};
  this->_created = QDateTime();
}

Contact::Contact(QString owner_id, QString user_id, QString username,
                 QDateTime created, QObject *parent)
    : Contact{parent} {
  this->_user_id = user_id;
  this->_owner_id = owner_id;
  this->_username = username;
  this->_created = created;
}

QString Contact::getUsername() { return this->_username; }
void Contact::setUsername(QString value) {
  this->_username = value;
  emit this->usernameChanged();
}

QString Contact::getOwnerId() { return this->_owner_id; }
void Contact::setOwnerId(QString value) {
  this->_owner_id = value;
  emit this->ownerIdChanged();
}

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

bool Contact::create() {
  // TODO: this is going to server;
  SqlContact *contact = new SqlContact(this);
  contact->setUserId(this->_user_id.toInt());
  contact->setOwnerId(this->_owner_id.toInt());
  contact->setUsername(this->_username);
  contact->setCreated(QDateTime::currentDateTime());

  if (!contact->createContact()) {
    emit this->creatingFail();
    return false;
  }

  emit this->successfullyCreated();
  return true;
};

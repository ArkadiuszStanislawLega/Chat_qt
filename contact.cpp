#include "contact.h"

Contact::Contact(QObject *parent) : QObject{parent} {
  this->_username = {};
  this->_id = {};
  this->_created = QDateTime();
}

Contact::Contact(QString id, QString username, QDateTime created,
                 QObject *parent) {
  this->_id = id;
  this->_username = username;
  this->_created = created;
}

void Contact::setUsername(QString value) { this->_username = value; }
QString Contact::getUsername() { return this->_username; }
void Contact::setId(QString value) { this->_id = value; }
QString Contact::getId() { return this->_id; }
QDateTime Contact::getCreated() { return this->_created; }

void Contact::setCreated(QDateTime value) {
  this->_created = value;
  emit this->created();
}

void Contact::remove() {
  // TODO: make remove from db;
  emit this->removed();
}

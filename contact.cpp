#include "contact.h"

Contact::Contact(QObject *parent) : QObject{parent} {
  this->_created = QDateTime();
}

Contact::Contact(int id, User *contact, QDateTime created, int ownerId, QObject *parent)
    : Contact{parent} {
  this->_id = id;
  this->_owner_id = ownerId;
  this->_contact = contact;
  this->_created = created;
}

int Contact::getContactId() { return this->_id; }
void Contact::setContactId(int value) { this->_id = value;  }
int Contact::getOwnerId() { return this->_owner_id; }

void Contact::setOwnerId(int value) { this->_owner_id = value; }

User *Contact::getContact() { return this->_contact; }

void Contact::setContact(User *value) { this->_contact = value; }

QDateTime Contact::getCreated() { return this->_created; }

int Contact::getId() const { return this->_id; }

void Contact::setId(int value) {
  if (this->_id == value)
    return;
  this->_id = value;
  emit this->contactIdChanged();

  this->setMessages({});
}

QList<Message *> Contact::getMessages() {
  qDebug() << this->_id << this->_owner_id;
  SqlContact *sqlContact = new SqlContact(this);
  sqlContact->setId(this->_id);
  sqlContact->setFirstUserId(this->_owner_id);
  sqlContact->setSecondUserId(this->_contact->getDbId().toInt());
    this->_messages = sqlContact->getMessages();
    qDebug() << "here I am!" << this->_messages.size();

  return this->_messages;
}

void Contact::setMessages(QList<Message *> values) {
  if (values.isEmpty()) {
    SqlContact *sqlContact = new SqlContact(this);
    sqlContact->setId(this->_id);
    sqlContact->setFirstUserId(this->_owner_id);
    this->_messages = sqlContact->getMessages();
    emit this->messagesChanged();
  } else {
    this->_messages = values;
  }
}

void Contact::setCreated(QDateTime value) { this->_created = value; }

void Contact::sendMessage(){

}

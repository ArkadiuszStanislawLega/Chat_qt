#include "contact.h"

Contact::Contact(QObject *parent) : QObject{parent} {
  this->_created = QDateTime();
}

Contact::Contact(int ownerId, User *contact, QDateTime created, QObject *parent)
    : Contact{parent} {
  this->_id = 0;
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

void Contact::setId(int value) { this->_id = value; }

QList<Message *> Contact::getMessages() {
  return this->_messages;
}

void Contact::setMessages(QList<Message *> values) {
  if (values.isEmpty()) {
    SqlContact *sqlContact = new SqlContact(this);
    sqlContact->setContactId(this->_id);
    this->_messages = sqlContact->getMessages();
    emit this->messagesChanged();
  } else {
    this->_messages = values;
  }
}

void Contact::setCreated(QDateTime value) { this->_created = value; }

void Contact::sendMessage(){

}

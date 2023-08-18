#include "contact.h"

Contact::Contact(QObject *parent) : QObject{parent} {
  this->_created = QDateTime();
}

Contact::Contact(int ownerId, User *contact, QDateTime created, QObject *parent)
    : Contact{parent} {
  this->_owner_id = ownerId;
  this->_contact = contact;
  this->_created = created;
}

int Contact::getOwnerId() { return this->_owner_id; }

void Contact::setOwnerId(int value) { this->_owner_id = value; }

User *Contact::getContact() { return this->_contact; }

void Contact::setContact(User *value) { this->_contact = value; }

QDateTime Contact::getCreated() { return this->_created; }

void Contact::setCreated(QDateTime value) { this->_created = value; }

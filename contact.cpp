#include "contact.h"

Contact::Contact(QObject *parent) : QObject{parent} {
  this->_created = QDateTime();
}

Contact::Contact(int id, User *user, QDateTime created, QObject *parent)
    : Contact{parent} {
  this->_contact_id = id;
  this->_user = user;
  this->_created = created;
}

int Contact::getContactId() { return this->_contact_id; }
void Contact::setContactId(int value) { this->_contact_id = value; }


User *Contact::getUser() { return this->_user; }
void Contact::setUser(User *value) { this->_user = value; }

QDateTime Contact::getCreated() { return this->_created; }

int Contact::getId() const { return this->_contact_id; }

void Contact::setId(int value) {
  if (this->_contact_id == value)
    return;
  this->_contact_id = value;
  emit this->contactIdChanged();

  this->setMessages({});
}

QList<Message *> Contact::getMessages() {
  SqlContact *sqlContact = new SqlContact(this);
  sqlContact->setId(this->_contact_id);
  //set user
  // sqlContact->setSecondUserId(this->_user->getDbId().toInt());
  this->_messages = sqlContact->getMessages();

  return this->_messages;
}

void Contact::setMessages(QList<Message *> values) {
  if (values.isEmpty()) {
    SqlContact *sqlContact = new SqlContact(this);
    sqlContact->setId(this->_contact_id);
    //sqlContact->setFirstUserId(this->_owner_id);
    this->_messages = sqlContact->getMessages();
    emit this->messagesChanged();
  } else {
    this->_messages = values;
  }
}

void Contact::setCreated(QDateTime value) { this->_created = value; }

void Contact::sendMessage() {}

bool Contact::deleteContact() {
  SqlContact *sql = new SqlContact(this);
  sql->setId(this->_contact_id);
  sql->setUserId(this->_user->getDbId().toInt());

  if (sql->deleteContact()) {
	emit succesfulDeleteContact();
	return true;
  } else {
	emit failToDeleteContact();
	return false;
  }
}

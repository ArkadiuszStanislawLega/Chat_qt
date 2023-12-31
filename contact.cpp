#include "contact.h"

Contact::Contact(QObject *parent)
	: QObject{parent} {
	this->_created = QDateTime();
}

Contact::Contact(int id, User *user, QDateTime created, QObject *parent)
	: Contact{parent} {
	this->_contact_id = id;
	this->_user = user;
	this->_created = created;
}

int Contact::getContactId() {
	return this->_contact_id;
}
void Contact::setContactId(int value) {
	this->_contact_id = value;
}

User *Contact::getUser() {
	return this->_user;
}
void Contact::setUser(User *value) {
	this->_user = value;
}

QDateTime Contact::getCreated() {
	return this->_created;
}

int Contact::getId() const {
	return this->_contact_id;
}

void Contact::setId(int value) {
	if (this->_contact_id == value)
		return;
	this->_contact_id = value;
	emit this->contactIdChanged();

	this->setMessages({});
}

QList<Message *> Contact::getMessages() {
	if (this->_contact_id <= 0)
		return this->_messages;

	SqlContact *sqlContact = new SqlContact(this);
	sqlContact->setId(this->_contact_id);
	this->_messages = sqlContact->getMessages();

	return this->_messages;
}

void Contact::setMessages(QList<Message *> values) {
	this->_messages = values;
}

void Contact::setCreated(QDateTime value) {
	this->_created = value;
}

/*!
 * \brief Contact::sendMessage Add to contact message in database. Before use rquired Set Contact Id and User Id (author of the messge).
 * \param text Text of the message.
 * \return True if message is successfully added to database.
 */
bool Contact::sendMessage(QString text) {
	if (this->_contact_id <= 0) {
		emit this->failedToSendMessage();
		return false;
	}

	if (!this->_user || this->_user->getDbId().toInt() <= 0) {
		emit this->failedToSendMessage();
		return false;
	}

	SqlContact *sql = new SqlContact(this);
	sql->setId(this->_contact_id);
	sql->setUserId(this->_user->getDbId().toInt());

	if (sql->sendMessage(text)) {
		delete sql;
		emit this->successfulySendedMessage();
		return true;
	}

	emit this->failedToSendMessage();
	delete (sql);
	return false;
}

/*!
 * \brief Contact::deleteContact Delete contact from database cascade with usercontact and messages. Before use required set Contact Id.
 * \return True if contact is successfuly removed from database.
 */
bool Contact::deleteContact() {
	if (this->_contact_id <= 0) {
		emit failToDeleteContact();
		return false;
	}

	SqlContact *sql = new SqlContact(this);
	sql->setId(this->_contact_id);

	if (sql->deleteContact()) {
		emit succesfulDeleteContact();
		delete sql;
		return true;
	}
	emit failToDeleteContact();
	delete sql;
	return false;
}

#include "message.h"

int Message::getId() const {
	return this->_id;
}

void Message::setId(int value) {
	if (this->_id == value)
		return;
	this->_id = value;
	emit idChanged();
}

int Message::getContactId() const {
	return this->_contact_id;
}

void Message::setContactId(int value) {
	if (this->_contact_id == value)
		return;
	this->_contact_id = value;
	emit ContactIdChanged();
}

QString Message::getAuthorId() const {
	return this->_authorId;
}

void Message::setAuthorId(QString value) {
	if (this->_authorId == value)
		return;
	this->_authorId = value;
	emit authorIdChanged();
}

QString Message::getAuthorUsername() const {
	return this->_author_username;
}

void Message::setAuthorUsername(const QString &value) {
	if (this->_author_username == value)
		return;
	this->_author_username = value;
	emit AuthorUsernameChanged();
}

QDateTime Message::getSentTimestamp() const {
	return this->_sentTimestamp;
}

void Message::setSentTimestamp(const QDateTime &value) {
	if (this->_sentTimestamp == value)
		return;
	this->_sentTimestamp = value;
	emit sentTimestampChanged();
}

QString Message::getText() const {
	return this->_text;
}

void Message::setText(const QString &value) {
	if (this->_text == value)
		return;
	this->_text = value;
	emit textChanged();
}

bool Message::sendMessage() {
	SqlMessage *sql = new SqlMessage(this);
	sql->setContactId(this->_contact_id);
	sql->setAuthorId(this->_authorId.toInt());
	sql->setText(this->_text);
	sql->setSentTimestamp(QDateTime::currentDateTime());

	return sql->createMessage();
}

Message::Message(QObject *parent)
	: QObject{parent} {}

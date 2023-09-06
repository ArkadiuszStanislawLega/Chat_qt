#include "sqlmessage.h"

bool SqlMessage::executeQuery(QSqlQuery &query) {
	qDebug() << "Sql Message executing: " << query.lastQuery();
	if (!query.exec()) {
		qDebug() << query.lastError() << query.lastQuery();
		return false;
	}
	return true;
}

SqlMessage::SqlMessage(QObject *parent)
	: QObject{parent} {
	this->_author_id = 0;
	this->_contact_id = 0;
	this->_author_username = "";
	this->_sentTimestamp = QDateTime::currentDateTime();
	this->_text = "";
}

int SqlMessage::getContactId() const {
	return this->_contact_id;
}
void SqlMessage::setContactId(int value) {
	this->_contact_id = value;
}

int SqlMessage::getAuthorId() {
	return this->_author_id;
}
void SqlMessage::setAuthorId(int value) {
	this->_author_id = value;
}

QString SqlMessage::getText() {
	return this->_text;
}
void SqlMessage::setText(QString value) {
	this->_text = value;
}

QString SqlMessage::getAuthorUsername() {
	return this->_author_username;
}
void SqlMessage::setAuthorUsername(QString value) {
	this->_author_username = value;
}

QDateTime SqlMessage::getSentTimestamp() {
	return this->_sentTimestamp;
}
void SqlMessage::setSentTimestamp(QDateTime value) {
	this->_sentTimestamp = value;
}

bool SqlMessage::createMessage() {
	QSqlQuery query;
	query.prepare("INSERT INTO " + *MESSAGES_TABLE_NAME + "(" + *CONTACT_ID_COLUMN_NAME + ","
				  + *AUTHOR_ID_COLUMN_NAME + "," + *TEXT_COLUMN_NAME + ","
				  + *SENT_TIMESTAMP_COLUMN_NAME + ")" + " VALUES ( :" + *CONTACT_ID_COLUMN_NAME
				  + ", :" + *AUTHOR_ID_COLUMN_NAME + ", :" + *TEXT_COLUMN_NAME
				  + ", :" + *SENT_TIMESTAMP_COLUMN_NAME + ";");
	query.bindValue(":" + *CONTACT_ID_COLUMN_NAME, this->_contact_id);
	query.bindValue(":" + *AUTHOR_ID_COLUMN_NAME, this->_author_id);
	query.bindValue(":" + *TEXT_COLUMN_NAME, this->_text);
	query.bindValue(":" + *SENT_TIMESTAMP_COLUMN_NAME, this->_sentTimestamp);

	return this->executeQuery(query);
}
/* TODO: Implement this.
 * Selected messages for contact query.
select
            sender.id as first_id,
            sender.username as first_username,
            reciver.id as second_id,
            reciver.username as second_username,
            Messages.author_id,
            Messages.text,
            Messages.sent_timestamp
            from Messages
INNER JOIN Contacts ON Contacts.id = Messages.contact_id
INNER JOIN Users as sender ON sender.id = Contacts.first_user_id
INNER JOIN Users as reciver ON reciver.id = Contacts.second_user_id
where Contacts.id = 1
ORDER BY Messages.sent_timestamp DESC;
*/

QString SqlMessage::buildQueryReadMessages() {
	return "SELECT " + *MESSAGES_TABLE_NAME + "." + *ID_COLUMN_NAME + ", " + *CONTACT_ID_COLUMN_NAME
		   + "," + *AUTHOR_ID_COLUMN_NAME + ", " + *USERS_TABLE_NAME + "." + *USERNAME_COLUMN_NAME
		   + ", " + *TEXT_COLUMN_NAME + ", " + *SENT_TIMESTAMP_COLUMN_NAME + " FROM "
		   + *MESSAGES_TABLE_NAME + " INNER JOIN " + *USERS_TABLE_NAME + " ON "
		   + *MESSAGES_TABLE_NAME + "." + *AUTHOR_ID_COLUMN_NAME + " = " + *USERS_TABLE_NAME + "."
		   + *ID_COLUMN_NAME + " WHERE " + *CONTACT_ID_COLUMN_NAME + " = :"
		   + *CONTACT_ID_COLUMN_NAME + " ORDER BY " + *SENT_TIMESTAMP_COLUMN_NAME + " DESC;";
}

Message *SqlMessage::getMessageFromQuery(QSqlQuery &query) {
	int messages_id_column, contact_id_column, author_username_column, author_id_column,
		text_column, sent_timestamp_column;

	messages_id_column = query.record().indexOf(*ID_COLUMN_NAME);
	contact_id_column = query.record().indexOf(*CONTACT_ID_COLUMN_NAME);

	author_id_column = query.record().indexOf(*AUTHOR_ID_COLUMN_NAME);
	author_username_column = query.record().indexOf(*USERNAME_COLUMN_NAME);

	text_column = query.record().indexOf(*TEXT_COLUMN_NAME);
	sent_timestamp_column = query.record().indexOf(*SENT_TIMESTAMP_COLUMN_NAME);

	Message *message = new Message(this);
	message->setId(query.value(messages_id_column).toInt());
	message->setContactId(query.value(contact_id_column).toInt());
	message->setAuthorId(query.value(author_id_column).toString());
	message->setAuthorUsername(query.value(author_username_column).toString());
	message->setText(query.value(text_column).toString());
	message->setSentTimestamp(query.value(sent_timestamp_column).toDateTime());
	return message;
}

QList<Message *> SqlMessage::readMessages() {
	QSqlQuery query;
	query.prepare(this->buildQueryReadMessages());
	query.bindValue(":" + *CONTACT_ID_COLUMN_NAME, this->_contact_id);

	if (!this->executeQuery(query))
		return {};

	QVector<Message *> messages;
	while (query.next()) {
		messages.push_back(this->getMessageFromQuery(query));
	}
	return messages;
}
bool SqlMessage::updateMessage() {
	return false;
}
bool SqlMessage::deleteMessage() {
	return false;
}

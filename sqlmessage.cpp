#include "sqlmessage.h"

/* TODO: Implement this.
 * Insert message query.
 * insert into Messages (contact_id, author_id, message, sended_time)
VALUES(1,1,"druga wiadomosc",  "2023-10-12T12:10:00");
 * /

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
where Messages.author_id = 1 and reciver.id = 2
ORDER BY Messages.sent_timestamp DESC	;
 */

int SqlMessage::getContactId() const { return this->_contact_id; }

void SqlMessage::setContactId(int value) { this->_contact_id = value; }

bool SqlMessage::executeQuery(QSqlQuery &query) {
  if (!query.exec()) {
    qDebug() << query.lastError() << query.lastQuery();
    return false;
  }
  return true;
}

SqlMessage::SqlMessage(QObject *parent) : QObject{parent} {}

int SqlMessage::getAuthorId() { return this->_author_id; }
void SqlMessage::setAuthorId(int value) { this->_author_id = value; }

int SqlMessage::getReceiverId() { return this->_receiver_id; }
void SqlMessage::setReceiverId(int value) { this->_receiver_id = value; }

QString SqlMessage::getText() { return this->_text; }
void SqlMessage::setText(QString value) { this->_text = value; }

QString SqlMessage::getAuthorUsername() { return this->_author_username; }
void SqlMessage::setAuthorUsername(QString value) {
  this->_author_username = value;
}

QString SqlMessage::getReceiverUsername() { return this->_receiver_username; }
void SqlMessage::setReceiverUsername(QString value) {
  this->_receiver_username = value;
}

QDateTime SqlMessage::getSentTimestamp() { return this->_sentTimestamp; }
void SqlMessage::setSentTimestamp(QDateTime value) {
  this->_sentTimestamp = value;
}

bool SqlMessage::createMessage() {
  QSqlQuery query;
  query.prepare("INSERT INTO " + *MESSAGES_TABLE_NAME + "(" +
                *CONTACT_ID_COLUMN_NAME + "," + *AUTHOR_ID_COLUMN_NAME + "," +
                *TEXT_COLUMN_NAME + "," + *SENT_TIMESTAMP_COLUMN_NAME + ")" +
                " VALUES ( :" + *CONTACT_ID_COLUMN_NAME +
                ", :" + *AUTHOR_ID_COLUMN_NAME + ", :" + *TEXT_COLUMN_NAME +
                ", :" + *SENT_TIMESTAMP_COLUMN_NAME + ";");
  query.bindValue(":" + *CONTACT_ID_COLUMN_NAME, this->_contact_id);
  query.bindValue(":" + *AUTHOR_ID_COLUMN_NAME, this->_author_id);
  query.bindValue(":" + *TEXT_COLUMN_NAME, this->_text);
  query.bindValue(":" + *SENT_TIMESTAMP_COLUMN_NAME, this->_sentTimestamp);

  return this->executeQuery(query);
}

bool SqlMessage::readMessage() { return false; }
bool SqlMessage::updateMessage() { return false; }
bool SqlMessage::deleteMessage() { return false; }

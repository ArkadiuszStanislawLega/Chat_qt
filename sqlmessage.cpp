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
                Messages.message,
                Messages.sended_time
                from Messages
INNER JOIN Contacts ON Contacts.id = Messages.contact_id
INNER JOIN Users as sender ON sender.id = Contacts.first_user
INNER JOIN Users as reciver ON reciver.id = Contacts.second_user
where Messages.author_id = 1
ORDER BY Messages.sended_time DESC	;
 */

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

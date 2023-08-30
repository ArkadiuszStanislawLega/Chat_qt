#include "sqlmessage.h"

/* TODO: Implement this.
 * Insert message query.
 * insert into Messages (contact_id, author_id, message, sended_time)
VALUES(1,1,"druga wiadomosc",  "2023-10-12T12:10:00");*/

int SqlMessage::getContactId() const { return this->_contact_id; }

void SqlMessage::setContactId(int value) { this->_contact_id = value; }

bool SqlMessage::executeQuery(QSqlQuery &query) {
  if (!query.exec()) {
    qDebug() << query.lastError() << query.lastQuery();
    return false;
  }
  return true;
}

SqlMessage::SqlMessage(QObject *parent) : QObject{parent} {
  this->_author_id = 0;
  this->_contact_id = 0;
  this->_receiver_id = 0;
  this->_receiver_username = "";
  this->_author_username = "";
  this->_sentTimestamp = QDateTime::currentDateTime();
  this->_text = "";
}

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
ORDER BY Messages.sent_timestamp DESC;
*/

QList<Message *> SqlMessage::readMessages() {
  QSqlQuery query;
  query.prepare(
      "SELECT sender." + *ID_COLUMN_NAME + " AS first_id, " + "sender." +
      *USERNAME_COLUMN_NAME + " AS first_username," + "receiver." +
      *ID_COLUMN_NAME + " as second_id," + "receiver." + *USERNAME_COLUMN_NAME +
      " as second_username," + *MESSAGES_TABLE_NAME + "." +
      *AUTHOR_ID_COLUMN_NAME + ", " + *MESSAGES_TABLE_NAME + "." +
      *TEXT_COLUMN_NAME + ", " + *MESSAGES_TABLE_NAME + "." +
      *SENT_TIMESTAMP_COLUMN_NAME + " from " + *MESSAGES_TABLE_NAME +
      " INNER JOIN " + *CONTACTS_TABLE_NAME + " ON " + *CONTACTS_TABLE_NAME +
      "." + *ID_COLUMN_NAME + " = " + *MESSAGES_TABLE_NAME + "." +
      *CONTACT_ID_COLUMN_NAME + " INNER JOIN " + *USERS_TABLE_NAME +
      " AS sender ON sender." + *ID_COLUMN_NAME + " = " + *CONTACTS_TABLE_NAME +
      "." + *ID_FIRST_USER_COLUMN_NAME + " INNER JOIN " + *USERS_TABLE_NAME +
      " AS receiver ON receiver." + *ID_COLUMN_NAME + " = " +
      *CONTACTS_TABLE_NAME + "." + *ID_SECOND_USER_COLUMN_NAME + " WHERE " +
      *MESSAGES_TABLE_NAME + "." + *AUTHOR_ID_COLUMN_NAME +
      " = :" + *AUTHOR_ID_COLUMN_NAME + " AND receiver." + *ID_COLUMN_NAME +
      " = :" + *ID_COLUMN_NAME + " ORDER BY " + *MESSAGES_TABLE_NAME + "." +
      *SENT_TIMESTAMP_COLUMN_NAME + " DESC;");

  query.bindValue(":" + *AUTHOR_ID_COLUMN_NAME, this->_author_id);
  query.bindValue(":" + *ID_COLUMN_NAME, this->_receiver_id);

  qDebug() << this->_author_id << this->_receiver_id << query.lastQuery();

  if (!this->executeQuery(query))
    return {};

  QVector<Message *> messages;
  while (query.next()) {
    int first_id_column, first_username_column, second_id_column,
        second_username_column, author_id_column, text_column,
        sent_timestamp_column;

    first_id_column = query.record().indexOf(FIRST_ID_COLUMN_NAME);
    second_id_column = query.record().indexOf(SECOND_ID_COLUMN_NAME);
    first_username_column = query.record().indexOf(FIRST_ID_COLUMN_NAME);
    second_username_column =
        query.record().indexOf(SECOND_USERNAME_COLUMN_NAME);
    author_id_column = query.record().indexOf(*AUTHOR_ID_COLUMN_NAME);
    text_column = query.record().indexOf(*TEXT_COLUMN_NAME);
    sent_timestamp_column = query.record().indexOf(*SENT_TIMESTAMP_COLUMN_NAME);

    Message *message = new Message(this);
    int firstId, secondId;

    firstId = query.value(first_id_column).toInt();
    secondId = query.value(second_id_column).toInt();

    message->setAuthorId(query.value(author_id_column).toInt());
    message->setMessage(query.value(text_column).toString());
    message->setSentTimestamp(query.value(sent_timestamp_column).toDateTime());

    if (message->getAuthorId() == firstId) {
      message->setSenderId(firstId);
      message->setReceiverId(secondId);
      message->setSenderUsername(query.value(first_username_column).toString());
      message->setReceiverUsername(
          query.value(second_username_column).toString());
    } else {
      message->setSenderId(secondId);
      message->setReceiverId(firstId);
      message->setSenderUsername(
          query.value(second_username_column).toString());
      message->setReceiverUsername(
          query.value(first_username_column).toString());
    }
    messages.push_back(message);
    qDebug() << message->getMessage();
  }
  return messages;
}
bool SqlMessage::updateMessage() { return false; }
bool SqlMessage::deleteMessage() { return false; }

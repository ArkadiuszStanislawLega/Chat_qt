#include "message.h"

Message::Message(QObject *parent) : QObject{parent} {}

int Message::getSenderId() const { return this->_senderId; }
void Message::setSenderId(const int &value) {
  if (this->_senderId == value)
    return;
  this->_senderId = value;
  emit this->senderIdChanged();
}

int Message::getReceiverId() const { return this->_receiverId; }
void Message::setReceiverId(const int &value) {
  if (this->_receiverId == value)
    return;
  this->_receiverId = value;
  emit this->receiverIdChanged();
}

int Message::getAuthorId() const { return this->_authorId; }
void Message::setAuthorId(const int &value) {
  if (this->_authorId == value)
    return;
  this->_authorId = value;
  emit this->authorIdChanged();
}

QString Message::getMessage() const { return this->_message; }
void Message::setMessage(const QString &value) {
  if (this->_message == value)
    return;
  this->_message = value;
  emit this->messageChanged();
}

QString Message::getReceiverUsername() const { return this->_receiverUsername; }
void Message::setReceiverUsername(const QString &value) {
  if (this->_receiverUsername == value)
    return;
  this->_receiverUsername = value;
  emit this->receiverUsernameChanged();
}

QString Message::getSenderUsername() const { return this->_senderUsername; }
void Message::setSenderUsername(const QString &value) {
  if (this->_senderUsername == value)
    return;
  this->_senderUsername = value;
  emit senderUsernameChanged();
}

QDateTime Message::getSentTimestamp() const { return _sentTimestamp; }
void Message::setSentTimestamp(const QDateTime &value) {
  if (this->_sentTimestamp == value)
    return;
  this->_sentTimestamp = value;
  emit sentTimestampChanged();
}

#ifndef SQLMESSAGE_H
#define SQLMESSAGE_H

#include <QObject>
#include <QDateTime>

#include "dbmanager.h"
#include "message.h"

class Message;
class SqlMessage : public QObject {


  Q_OBJECT
private:
  int _contact_id, _author_id, _receiver_id;
  QString _text, _author_username, _receiver_username;
  QDateTime _sentTimestamp;

  bool executeQuery(QSqlQuery &);

public:
  explicit SqlMessage(QObject *parent = nullptr);

  int getAuthorId();
  void setAuthorId(int);

  int getReceiverId();
  void setReceiverId(int);

  QString getText();
  void setText(QString);

  QString getAuthorUsername();
  void setAuthorUsername(QString);

  QString getReceiverUsername();
  void setReceiverUsername(QString);

  QDateTime getSentTimestamp();
  void setSentTimestamp(QDateTime);

  bool createMessage();
  bool readMessage();
  bool updateMessage();
  bool deleteMessage();

  int getContactId() const;
  void setContactId(int);

signals:
};

#endif // SQLMESSAGE_H

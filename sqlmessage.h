#ifndef SQLMESSAGE_H
#define SQLMESSAGE_H

#include <QDateTime>
#include <QList>
#include <QObject>

#include "dbmanager.h"
#include "message.h"

class Message;
class SqlMessage : public QObject {
	Q_OBJECT
private:
	int _contact_id, _author_id;
	QString _text, _author_username;
	QDateTime _sentTimestamp;
	QString buildQueryReadMessages();

	bool executeQuery(QSqlQuery &);
	Message *getMessageFromQuery(QSqlQuery &);

public:
  explicit SqlMessage(QObject *parent = nullptr);

  int getAuthorId();
  void setAuthorId(int);

  QString getText();
  void setText(QString);

  QString getAuthorUsername();
  void setAuthorUsername(QString);

  QDateTime getSentTimestamp();
  void setSentTimestamp(QDateTime);

  bool createMessage();
  QList<Message *> readMessages();
  bool updateMessage();
  bool deleteMessage();

  int getContactId() const;
  void setContactId(int);

signals:
};

#endif // SQLMESSAGE_H

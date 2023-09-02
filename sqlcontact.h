#ifndef SQLCONTACT_H
#define SQLCONTACT_H

#include <QObject>
#include <QDateTime>
#include <QList>

#include "dbmanager.h"
#include "contact.h"
#include "user.h"
#include "sqlmessage.h"
#include "message.h"

class Contact;
class User;
class SqlMessage;
class Message;
class SqlContact : public QObject
{
  Q_OBJECT
public:
  explicit SqlContact(QObject *parent = nullptr);

  bool connectUsersWithContact(int, int);
  bool createContact(const QDateTime &);
  bool createUserContact(int &);
  bool readContact();
  bool updateContact();
  bool deleteContact();
  QVector<Contact *> get_user_contacts();

  QDateTime getCreatedTimestamp();
  void setCreatedTimestamp(QDateTime value);

  bool sendMessage(QString);

  int getUserId();
  void setUserId(int);

  int getId() const;
  void setId(int newId);

  QList<Message *> getMessages();
  void setMessages(QList<Message *>);

signals:

private:
  int _id{}, _user_id{};
  QDateTime _created_timestamp{};
  QList<Message *> _messages;

  QList<Contact *> getContactsFromQuery(QSqlQuery &, QList<QString>);
  bool executeQuery(QSqlQuery &);
  QString selectContactsQuery();
};

#endif // SQLCONTACT_H

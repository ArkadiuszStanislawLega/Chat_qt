#ifndef CONTACT_H
#define CONTACT_H

#include <QDateTime>
#include <QObject>

#include "message.h"
#include "sqlcontact.h"
#include "sqluser.h"
#include "user.h"

class User;
class Message;
class SqlContact;
class Contact : public QObject {
  Q_OBJECT
public:
  explicit Contact(QObject *parent = nullptr);
  Contact(int id, User *contact, QDateTime created, QObject *parent = nullptr);

  Q_PROPERTY(int contactId READ getContactId WRITE setContactId NOTIFY
                 contactIdChanged FINAL)
  Q_PROPERTY(User *user READ getUser WRITE setUser NOTIFY userChanged FINAL)
  Q_PROPERTY(
      QDateTime created READ getCreated WRITE setCreated NOTIFY createdChanged)
  Q_PROPERTY(QList<Message *> messages READ getMessages WRITE setMessages NOTIFY
                 messagesChanged FINAL)

  int getContactId();
  void setContactId(int);

  User *getUser();
  void setUser(User *value);

  void setCreated(QDateTime value);
  QDateTime getCreated();

  int getId() const;
  void setId(int);

  QList<Message *> getMessages();
  void setMessages(QList<Message *>);

  signals:
  void contactIdChanged();
  void ownerIdChanged();
  void userChanged();
  void createdChanged();
  void messagesChanged();
  void failedToSendMessage();
  void successfulySendedMessage();
  void succesfulDeleteContact();
  void failToDeleteContact();

  public slots:
	  bool sendMessage(QString);
	  bool deleteContact();

  private:
  int _contact_id;
  User *_user;
  QDateTime _created;
  QList<Message *> _messages;
};

#endif // CONTACT_H

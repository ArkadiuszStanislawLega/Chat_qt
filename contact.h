#ifndef CONTACT_H
#define CONTACT_H

#include <QDateTime>
#include <QObject>

#include "user.h"

class User;
class Contact : public QObject {
  Q_OBJECT
      public:
               explicit Contact(QObject *parent = nullptr);
  Contact(int owner_id, User *contact, QDateTime created,
          QObject *parent = nullptr);

  Q_PROPERTY(int ownerId READ getOwnerId WRITE setOwnerId)
  Q_PROPERTY(User *contact READ getContact WRITE setContact)
  Q_PROPERTY(QDateTime created READ getCreated WRITE setCreated)

  int getOnwerId();
  void setOnwerId(int value);

  User *getContact();
  void setContact(User *value);

  void setCreated(QDateTime value);
  QDateTime getCreated();

signals:

private:
  int _owner_id;
  User *_contact;
  QDateTime _created;
};

#endif // CONTACT_H

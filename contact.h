#ifndef CONTACT_H
#define CONTACT_H

#include <QDateTime>
#include <QObject>

#include "user.h"
#include "sqluser.h"

class User;
class Contact : public QObject {
  Q_OBJECT
      public:
               explicit Contact(QObject *parent = nullptr);
  Contact(int owner_id, User *contact, QDateTime created,
          QObject *parent = nullptr);

  Q_PROPERTY(int contactId READ getContactId WRITE setContactId NOTIFY
                 contactIdChanged FINAL)
  Q_PROPERTY(User *contact READ getContact WRITE setContact NOTIFY
                 contactChanged FINAL)
  Q_PROPERTY(
      QDateTime created READ getCreated WRITE setCreated NOTIFY createdChanged)

  int getContactId();
  void setContactId(int);

  int getOwnerId();
  void setOwnerId(int value);

  User *getContact();
  void setContact(User *value);

  void setCreated(QDateTime value);
  QDateTime getCreated();

  int getId() const;
  void setId(int);

signals:
  void contactIdChanged();
  void ownerIdChanged();
  void contactChanged();
  void createdChanged();

public slots:
  void sendMessage();

  private:
    int _id, _owner_id;
  User *_contact;
  QDateTime _created;
};

#endif // CONTACT_H

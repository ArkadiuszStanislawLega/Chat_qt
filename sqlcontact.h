#ifndef SQLCONTACT_H
#define SQLCONTACT_H

#include <QObject>
#include <QDateTime>

#include "dbmanager.h"
#include "contact.h"
#include "user.h"

class Contact;
class User;
class SqlContact : public QObject
{
  Q_OBJECT
public:
  explicit SqlContact(QObject *parent = nullptr);

  bool createContact();
  bool readContact();
  bool updateContact();
  bool deleteContact();

  static QVector<Contact> get_all();
  static QVector<Contact> get_user_contacts(int userId);

  int getContactId();
  void setContactId(int value);
  int getOwnerId();
  void setOwnerId(int value);
  int getUserId();
  void setUserId(int value);
  QString getUsername();
  void setUsername(QString value);
  QDateTime getCreated();
  void setCreated(QDateTime value);

signals:

private:
  int _contact_id{}, _owner_id{}, _user_id;
  QString _username{};
  QDateTime _created{};
};

#endif // SQLCONTACT_H

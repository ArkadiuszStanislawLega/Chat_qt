#ifndef SQLCONTACT_H
#define SQLCONTACT_H

#include <QObject>
#include <QDateTime>

#include "dbmanager.h"
#include "contact.h"
#include "user.h"
#include "sqlmessage.h"

class Contact;
class User;
class SqlMessage;
class SqlContact : public QObject
{
  Q_OBJECT
public:
  explicit SqlContact(QObject *parent = nullptr);

  bool createContact();
  bool readContact();
  bool updateContact();
  bool deleteContact();
  QVector<Contact *> get_user_contacts();

  QDateTime getCreatedTimestamp();
  void setCreatedTimestamp(QDateTime value);

  bool sendMessage(QString);

  int getFirstUserId();
  void setFirstUserId(int);

  int getSecondUserId() const;
  void setSecondUserId(int);

  int getContactId() const;
  void setContactId(int);

  int getId() const;
  void setId(int newId);

signals:

private:
  int _id, _contact_id{}, _first_user_id{}, _second_user_id;
  QDateTime _created_timestamp{};

  bool isAddingContactComplited();
  bool executeQuery(QSqlQuery &);
};

#endif // SQLCONTACT_H

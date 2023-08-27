#ifndef SQLUSER_H
#define SQLUSER_H

#include <QDateTime>
#include <QObject>
#include <QPair>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QVector>

#include "dbmanager.h"
#include "user.h"
#include "contact.h"
#include "sqlcontact.h"

class User;
class Contact;
class SqlContact;
class SqlUser : public QObject {
  Q_OBJECT
public:
  explicit SqlUser(QObject *parent = nullptr);
  static QString getNextId();
  static SqlUser *getUserByPasswordAndUsername(QString username, QString password);

  bool createUser();
  bool isAddingUserComplieted();
  bool isCredentialsCorrect(int id, QString password);
  bool readUser();
  bool updateUser();
  bool deleteUser();

  bool sendMessage();

  int getId();
  void setId(int value);

  QString getUsername();
  void setUsername(QString value);

  QString getPassword();
  void setPassword(QString value);

  QDateTime getOccupied();
  void setOccupied(QDateTime value);

  QDateTime getLastActivity();
  void setLastActivity(QDateTime value);

  void userToSqlUserConverter(User &user);

  bool createContact(int contact_id);
  bool removeContact(int contact);
  QVector<Contact *> getContacts();

  private:
  QString _username{}, _password{};
  int _id{};
  QDateTime _occupied{}, _last_activity{};

  // TODO: Make field keeping avatar image.
};

#endif // SQLUSER_H

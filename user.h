#ifndef USER_H
#define USER_H

#include <QCryptographicHash>
#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>

#include "contact.h"
#include "dbmanager.h"
#include "sqluser.h"

class Contact;
class SqlUser;
class User : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY
                 usernameChanged FINAL)
  Q_PROPERTY(QString dbId READ getDbId WRITE setDbId NOTIFY idChanged FINAL)
  Q_PROPERTY(QVector<Contact> contacts READ getContacts WRITE setContacts NOTIFY
                 contactsChanged FINAL)

public:
  explicit User(QObject *parent = nullptr);
  User(QString id, QString username, QVector<Contact> contacts,
       QObject *parent = nullptr);

  QString getUsername();
  QString getDbId();
  QVector<Contact> getContacts();

  void setUsername(QString username);
  void setDbId(QString id);
  void setContacts(QVector<Contact> contacts);
  void sqlUserToUserConverter(SqlUser &user);

signals:
  void createdConfirmed();
  void createdError();
  void usernameChanged();
  void passwordChanged();
  void idChanged();
  void isLoginIn();
  void loginInFail();
  void contactsChanged();

public slots:
  void registerUser(QString *password);
  void isUserLogin(QString *password);

private:
  QString _id;
  QString _username;
  QVector<Contact> _contacts;
  QSqlDatabase _database;

  void addUserToDb();
  bool auteticateUser(QString *password);
  bool addContact(Contact &contact);
  bool removeContact(Contact &contact);
};
#endif // USER_H

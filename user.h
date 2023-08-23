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
  Q_PROPERTY(
      QVector<Contact *> contacts READ getContacts WRITE setContacts NOTIFY contactsChanged FINAL)

  private:
  QString _id;
  QString _username;
  QVector<Contact *> _contacts;
  QSqlDatabase _database;

  bool addContact(Contact &contact);
  bool removeContact(Contact &contact);

public slots:
  void addUserToDb(QString);
  void isUserLogin(QString);
  void createContact(QString);
  bool auteticateUser(QString);

public:
  explicit User(QObject *parent = nullptr);
  User(QString id, QString username, QVector<Contact *> contacts, QObject *parent = nullptr);

  QString getUsername();
  void setUsername(QString username);

  QString getDbId();
  void setDbId(QString id);

  QVector<Contact *> getContacts();
  void setContacts(QVector<Contact *> contacts);

  void sqlUserToUserConverter(SqlUser &user);

signals:
  void createdConfirmed();
  void createdError();
  void usernameChanged();
  void idChanged();
  void isLoginIn();
  void loginInFail();
  void contactsChanged();
  void contactCreated();
  void failToCreateContact();

};
#endif // USER_H

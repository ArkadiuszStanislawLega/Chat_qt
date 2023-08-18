#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <QDateTime>

#include "sqlcontact.h"
#include "sqluser.h"

class Contact : public QObject
{
  Q_OBJECT
public:
  explicit Contact(QObject *parent = nullptr);
  Contact(QString owner_id, QString user_id, QString username, QDateTime created, QObject *parent = nullptr);

  Q_PROPERTY(QString userId READ getUserId WRITE setUserId NOTIFY userIdChanged FINAL)
  Q_PROPERTY(QString ownerId READ getOwnerId WRITE setOwnerId NOTIFY ownerIdChanged FINAL)
  Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY
                 usernameChanged FINAL);
  Q_PROPERTY(QDateTime created READ getCreated WRITE setCreated NOTIFY
                 createdChanged FINAL)

  // TODO: avatar property
  void setUsername(QString value);
  QString getUsername();

  void setOwnerId(QString value);
  QString getOwnerId();

  void setUserId(QString value);
  QString getUserId();

  void setCreated(QDateTime value);
  QDateTime getCreated();

signals:
  void userUpdated();
  void created();
  void removed();
  void usernameChanged();
  void createdChanged();
  void userIdChanged();
  void ownerIdChanged();
  void idChanged();
  void successfullyCreated();
  void creatingFail();

public slots:
  void remove();
  bool create();

private:
  QString _owner_id, _user_id, _username;
  QDateTime _created;
};

#endif // CONTACT_H

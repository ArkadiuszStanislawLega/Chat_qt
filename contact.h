#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <QDateTime>

class Contact : public QObject
{
  Q_OBJECT
public:
  explicit Contact(QObject *parent = nullptr);
  Contact(QString id, QString username, QDateTime created, QObject *parent = nullptr);
  Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY
                 usernameChanged FINAL);
  Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged FINAL)
  Q_PROPERTY(QDateTime created READ getCreated WRITE setCreated NOTIFY
                 createdChanged FINAL)

  // TODO: avatar property
  void setUsername(QString value);
  QString getUsername();

  void setId(QString value);
  QString getId();

  QDateTime getCreated();
  void setCreated(QDateTime value);

signals:
  void userUpdated();
  void created();
  void removed();
  void usernameChanged();
  void createdChanged();
  void idChanged();

public slots:
  void remove();

private:
  QString _username;
  QString _id;
  QDateTime _created;
};

#endif // CONTACT_H

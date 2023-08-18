#ifndef SQLCONTACT_H
#define SQLCONTACT_H

#include <QObject>
#include <QDateTime>


class sqlContact : public QObject
{
  Q_OBJECT
public:
  explicit sqlContact(QObject *parent = nullptr);

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
  bool createContact();
  bool readContact();
  bool updateContact();
  bool deleteContact();

private:
  int _contact_id{}, _owner_id{}, _user_id;
  QString _username{};
  QDateTime _created{};
};

#endif // SQLCONTACT_H

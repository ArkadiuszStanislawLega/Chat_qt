#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDebug>
#include <QCryptographicHash>

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY created FINAL)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY created FINAL)
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY created FINAL)


public:
    explicit User(QObject *parent = nullptr);

    QString getPassword();
    QString getUsername();
    QString getId();

    void setPassword(QString password);
    void setUsername(QString username);
    void setId(QString id);

signals:
    void created();

public slots:

private:
    QString _password;
    QString _username;
    QString _id;

};


#endif // USER_H

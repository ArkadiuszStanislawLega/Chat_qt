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
    Q_PROPERTY(QString dbId READ getDbId WRITE setDbId NOTIFY created FINAL)


public:
    explicit User(QObject *parent = nullptr);

    QString getPassword();
    QString getUsername();
    QString getDbId();

    void setPassword(QString password);
    void setUsername(QString username);
    void setDbId(QString id);

signals:
    void created();

public slots:
    void registration();

private:
    QString _password;
    QString _username;
    QString _id;

};


#endif // USER_H

#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDebug>
#include <QCryptographicHash>

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY created FINAL)
public:
    explicit User(QObject *parent = nullptr);

    QString getPassword();
    void setPassword(QString password);

signals:
    void created();

public slots:

private:
    QString _password;

};


#endif // USER_H

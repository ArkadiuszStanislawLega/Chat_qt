#ifndef REGISTER_H
#define REGISTER_H

#include <QObject>
#include <QDebug>
#include <QCryptographicHash>

class Register : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY created FINAL)
public:
    explicit Register(QObject *parent = nullptr);

    QString getPassword();
    void setPassword(QString password);

signals:
    void created();

public slots:

private:
    QString _password;

};


#endif // REGISTER_H

#include "user.h"

User::User(QObject *parent)
    : QObject{parent}
{

}

QString User::getPassword(){
    return this->_password;
}

void User::setPassword(QString password){
    this->_password = password;
    qDebug() << "setPassword:" << password;
    emit this->created();
}

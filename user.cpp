#include "user.h"

User::User(QObject *parent)
    : QObject{parent}
{

}

QString User::getPassword(){
    return this->_password;
}

QString User::getUsername(){
    return this->_username;

}

QString User::getId(){
    return this->_id;
}

void User::setPassword(QString password){
    this->_password = password;
    qDebug() << "setPassword:" << password;
    emit this->created();
}

void User::setUsername(QString username){
    this->_username = username;
    qDebug() << "setUsername:" << username;
    emit this->created();

}

void User::setId(QString id){
    this->_id = id;
    qDebug() << "setId:" << id;
    emit this->created();
}

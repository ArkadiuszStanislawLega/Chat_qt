#include "user.h"

User::User(QObject *parent)
    : QObject{parent}{
    this->_id = "1";
    this->_password = "";
    this->_username = "";

    //TODO: Get from server free id.
}

QString User::getPassword(){
    return this->_password;
}

QString User::getUsername(){
    return this->_username;

}

QString User::getDbId(){
    return this->_id;
}

void User::setPassword(QString password){
    this->_password = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());
    qDebug() << "setPassword:" << this->_password;
}

void User::setUsername(QString username){
    this->_username = username;
    qDebug() << "setUsername:" << username;

}

void User::setDbId(QString id){
    this->_id = id;
    qDebug() << "setId:" << id;
}

void User::registerUser(){
    qDebug() << "register";
    emit this->createdConfirmed();
    emit this->createdError();

}

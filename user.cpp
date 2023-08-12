#include "user.h"

User::User(QObject *parent)
    : QObject{parent}{
    this->_id = "2";
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
    this->addUserToDb();
}

void User::addUserToDb(){
    //TODO: Move this to server.

        QSqlQuery query;
        //TODO: Change insert into to update - after create server.
        query.prepare("INSERT INTO " + *USERS_TABLE_NAME + " values('" + this->_id + "', '" + this->_username + "','" + this->_password + "');");
        if(query.exec()){
            emit this->createdConfirmed();
        } else {
            qDebug() << query.lastError().text();
            emit this->createdError();
        }
}

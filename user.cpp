#include "user.h"

User::User(QObject *parent)
    : QObject{parent}{

    this->_id = "1";
    this->_password = "";
    this->_username = "";

    //TODO: Move this to server. Get empty id from server.
    QSqlQuery query;
    query.prepare("SELECT MAX(" + *ID_COLUMN_NAME + ") from " + *USERS_TABLE_NAME + ";");
    if(query.exec()){
        while(query.next()){
            int db_next_id = query.value(0).toInt();
            db_next_id++;
            this->_id = QString::number(db_next_id);
        }
    }
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

void User::isUserLogin(){
    if(this->auteticateUser()) emit this->isLoginIn();
    else emit this->loginInFail();
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

bool User::auteticateUser(){
    //TODO: Move this to server.
    QSqlQuery query;
    query.prepare(*SELECT_ALL + " " + *USERS_TABLE_NAME + " WHERE "+ *ID_COLUMN_NAME + " = '" + this->_id + "';");
    if(query.exec()){
        while(query.next()){
            int password_column {}, username_column {};

            password_column = query.record().indexOf(*PASSWORD_COLUMN_NAME);
            username_column = query.record().indexOf(*USERNAME_COLUMN_NAME);

            if( query.value(password_column).toString() == this->_password){
                this->_username = query.value(username_column).toString();
                return true;
            } else
                return false;
        }
    }
    return false;
}

#include "sqluser.h"

SqlUser::SqlUser(QObject *parent)
    : QObject{parent}{
}

void SqlUser::createTable(){

}

QString SqlUser::getNextId(){
    QSqlQuery query;
    query.prepare("SELECT MAX(" + *ID_COLUMN_NAME + ") from " + *USERS_TABLE_NAME + ";");
    if(query.exec()){
        while(query.next()){
            int db_next_id = query.value(0).toInt();
            db_next_id++;
            return QString::number(db_next_id);
        }
    }
    return "-1";
}

bool SqlUser::createUser(){
    QSqlQuery query;

    query.prepare("INSERT INTO " + *USERS_TABLE_NAME + " VALUES(:id,:username,:password);");
    query.bindValue(":id", this->_id);
    query.bindValue(":username", this->_username);
    query.bindValue(":password", this->_password);

    if(query.exec()){
        return true;
    } else {
        qDebug() << query.lastError().text();
        return false;
    }
    return false;
}

bool SqlUser::readUser(){
    QSqlQuery query;
    query.prepare("SELECT * FROM "+ *USERS_TABLE_NAME +" WHERE id = :id;");
    query.bindValue(":id", this->_id);

    qDebug() << query.lastQuery();

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
    } else qDebug() << query.lastQuery() << query.lastError();
    return false;
}

bool SqlUser::updateUser(){
    return false;
}

bool SqlUser::deleteUser(){
    return false;
}

QString SqlUser::getId(){
    return this->_id;
}

void SqlUser::setId(QString value){
    this->_id = value;
}

QString SqlUser::getUsername(){
    return this->_username;
}

void SqlUser::setUsername(QString value){
    this->_username = value;
}

QString SqlUser::getPassword(){
    return this->_password;
}

void SqlUser::setPassword(QString value){
    this->_password = value;
}

QDateTime SqlUser::getOccupied(){
    return this->_occupied;
}

void SqlUser::setOccupied(QDateTime value){
    this->_occupied = value;
}

QDateTime SqlUser::getLastActivity(){
    return this->_last_activity;
}

void SqlUser::setLastActivity(QDateTime value){
    this->_last_activity = value;
}

void SqlUser::userToSqlUserConverter(User &user){
    this->_id = user.getDbId();
    this->_username = user.getUsername();
    this->_password = user.getPassword();
}



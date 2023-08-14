#include "sqluser.h"

SqlUser::SqlUser(QObject *parent)
    : QObject{parent}{
}

void SqlUser::createTable(){
    QSqlQuery query;
    query.prepare( *CREATE_TABLE + " '" + *USERS_TABLE_NAME + "' ("
                   "'" + *ID_COLUMN_NAME + "' INTEGER NOT NULL UNIQUE, "
                   "'" + *USERNAME_COLUMN_NAME + "' TEXT" + ", "
                   "'" + *PASSWORD_COLUMN_NAME + "' " + *TEXT_NO_NULL + "); "
                  );
    if(!query.exec()){
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }
}

QString SqlUser::getNextId(){
    QSqlQuery query;
    query.prepare("SELECT MAX(" + *ID_COLUMN_NAME + ") from " + *USERS_TABLE_NAME + ";");
    if(query.exec()){
        while(query.next()){
            int db_next_id = query.value(0).toInt();
            db_next_id++;
            qDebug() << "next " << db_next_id;
            return QString::number(db_next_id);
        }
    }
    return "-1";
}

bool SqlUser::genericCreate(QString table, QVector<QPair<QString,QString>> args){
    if(table.isEmpty()) return false;
    if(args.size() == 0) return false;

    QString     cmd = "INSERT INTO " + table,
                properties {"("},
                values {" VALUES("};

    for(int i = 0; i < args.size(); i++){
        properties += args[i].first;
        values += ":" + args[i].first;

        if(i < args.size()-1){
            properties += ",";
            values += ",";
        } else {
            properties += ")";
            values += ")";
        }
    }

    cmd += properties + values + ";";

    QSqlQuery query;
    query.prepare(cmd);

    for(const QPair<QString, QString> &pair : args){
        QString key = ":" + pair.first;
        query.bindValue(key, pair.second);
    }

    qDebug() << query.lastQuery();

    if(query.exec()){
        return true;
    } else {
        qDebug() << query.lastError().text();
        return false;
    }
}

bool SqlUser::createUser(){
    QVector<QPair<QString, QString>> args =
    {
        {*ID_COLUMN_NAME, QString::number(this->_id)},
        {*USERNAME_COLUMN_NAME, this->_username},
        {*PASSWORD_COLUMN_NAME, this->_password}
    };
    return this->genericCreate(*USERS_TABLE_NAME, args);
}

bool SqlUser::readUser(){
    QSqlQuery query;
    query.prepare("SELECT * FROM "+ *USERS_TABLE_NAME +" WHERE id = :id;");
    query.bindValue(":id", this->_id);

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

int SqlUser::getId(){
    return this->_id;
}

void SqlUser::setId(int value){
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
    this->_id = user.getDbId().toInt();
    this->_username = user.getUsername();
    this->_password = user.getPassword();
}



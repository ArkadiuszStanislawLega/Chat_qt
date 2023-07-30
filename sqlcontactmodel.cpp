#include "sqlcontactmodel.h"


static void createTable(){
    if(QSqlDatabase::database().tables().contains(*CONTACTS_TABLE_NAME)){
        return;
    }

    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS '" + *CONTACTS_TABLE_NAME + "' ('" + *NAME_COLUMN + "' TEXT NOT NULL, PRIMARY KEY(" + *NAME_COLUMN + "))" );
    if(!query.exec()) {
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }

    query.exec("INSERT INTO " + *CONTACTS_TABLE_NAME + " VALUES('Albert Einstein')");
    query.exec("INSERT INTO " + *CONTACTS_TABLE_NAME + " VALUES('Ernest Hemingway')");
    query.exec("INSERT INTO " + *CONTACTS_TABLE_NAME + " VALUES('Hans Gude')");
}

SqlContactModel::SqlContactModel(QObject *parent) : QSqlQueryModel(parent){
    createTable();

    QSqlQuery query;
    query.prepare("SELECT * FROM " + *CONTACTS_TABLE_NAME);
    if(!query.exec()){
        qFatal("Contacts Select query failed: %s", qPrintable(query.lastError().text()));
    }

    qDebug() << query.result();

    setQuery(std::move(query));

    if(lastError().isValid()){
        qFatal("Cannot set query on SqlContactModel: %s: ", qPrintable(lastError().text()));
    }
}

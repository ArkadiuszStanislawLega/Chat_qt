#include "sqlcontactmodel.h"


static void createTable(){
}

SqlContactModel::SqlContactModel(QObject *parent) : QSqlQueryModel(parent){
    createTable();

    QSqlQuery query;
    query.prepare("SELECT * FROM " + *CONTACTS_TABLE_NAME);
    if(!query.exec()){
        qFatal("Contacts Select query failed: %s", qPrintable(query.lastError().text()));
    }

    setQuery(std::move(query));

    if(lastError().isValid()){
        qFatal("Cannot set query on SqlContactModel: %s: ", qPrintable(lastError().text()));
    }
}

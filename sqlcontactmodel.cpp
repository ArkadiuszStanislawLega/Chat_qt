#include "sqlcontactmodel.h"


SqlContactModel::SqlContactModel(QObject *parent) : QSqlQueryModel(parent){
    QSqlQuery query;
  query.prepare("SELECT " + *ID_SECOND_USER_COLUMN_NAME + ", " + *CREATE_TIMESTAMP_COLUMN_NAME + ", "
                  + *USERNAME_COLUMN_NAME + " FROM " + *CONTACTS_TABLE_NAME + " INNER JOIN "
                  + *USERS_TABLE_NAME + " ON " + *USERS_TABLE_NAME + "." + *ID_COLUMN_NAME + " = "
                  + *CONTACTS_TABLE_NAME + "." + *ID_SECOND_USER_COLUMN_NAME + " WHERE "
                  + *ID_FIRST_USER_COLUMN_NAME + " = :" + *ID_FIRST_USER_COLUMN_NAME + ";");
    if(!query.exec()){
        qFatal("Contacts Select query failed: %s", qPrintable(query.lastError().text()));
    }

    setQuery(std::move(query));

    if(lastError().isValid()){
        qFatal("Cannot set query on SqlContactModel: %s: ", qPrintable(lastError().text()));
    }
}

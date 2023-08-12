#include "dbmanager.h"

DbManager::DbManager(QObject *parent) : QObject(parent) {
    this->_database = QSqlDatabase::addDatabase("QSQLITE");
    this->_database.setDatabaseName(*DATABASE_NAME);

    if(!this->_database.open()){
        qDebug() << "Error during connecting to databse.";
    }else{
        qDebug() << "Db connection is ok.";
        this->CreateTables();
    }
}

void DbManager::CreateTables(){
    this->CreateContactsTable();
    this->CreateConversationTable();
    this->CreateUsersTable();
}

void DbManager::CreateContactsTable(){
    QSqlQuery query;
    query.prepare( *CREATE_TABLE + " '" + *CONTACTS_TABLE_NAME +
                  "' ('" + *NAME_COLUMN + "' " + *TEXT_NO_NULL + ", " + *PRIMARY_KEY + "(" + *NAME_COLUMN + "))" );
    if(!query.exec()) {
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }
}

void DbManager::CreateConversationTable(){
    QSqlQuery query;
    query.prepare( *CREATE_TABLE + " '" + *CONVERSATION_TABLE_NAME + "' ("
                            "'" + *AUTHOR_COLUMN + "' " + *TEXT_NO_NULL + ", "
                    "'" + *RECIPIENT_COLUMN + "' "+ *TEXT_NO_NULL + ", "
                       "'" + *TIME_COLUMN + "' " + *TEXT_NO_NULL + ", "
                  "'" + *MESSAGE_COLUMN + "' " + *TEXT_NO_NULL + ", "
                     "FOREIGN KEY('" + *AUTHOR_COLUMN + "') REFERENCES " + *CONTACTS_TABLE_NAME+ "(" + *NAME_COLUMN + "),"
                                                                                                    "FOREIGN KEY('" + *RECIPIENT_COLUMN + "') REFERENCES " +  *CONTACTS_TABLE_NAME + "(" + *NAME_COLUMN + ")"
                                                                                                       ")");
    if(!query.exec()) {
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }
}

void DbManager::CreateUsersTable(){
    QSqlQuery query;

    query.prepare( *CREATE_TABLE + " '" + *USERS_TABLE_NAME + "' ("
                                  "'" + *ID_COLUMN_NAME + "' " + *TEXT_NO_NULL + " UNIQUE, "
                                    "'" + *USERNAME_COLUMN_NAME + "' TEXT" + ", "
                    "'" + *PASSWORD_COLUMN_NAME + "' " + *TEXT_NO_NULL + "); "
                  );
    qDebug() << query.lastQuery();
    if(!query.exec()){
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }
}

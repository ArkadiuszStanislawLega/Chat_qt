#ifndef SQLCONTACTMODEL_H
#define SQLCONTACTMODEL_H

#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

Q_GLOBAL_STATIC(QString, CONTACTS_TABLE_NAME, "Contacts");
Q_GLOBAL_STATIC(QString, NAME_COLUMN, "name");

class SqlContactModel : public QSqlQueryModel{
public:
    Q_OBJECT
public:
    SqlContactModel(QObject *parent = nullptr);
};
#endif // SQLCONTACTMODEL_H

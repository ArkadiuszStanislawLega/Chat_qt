#ifndef SQLCONTACTMODEL_H
#define SQLCONTACTMODEL_H

#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

class SqlContactModel : public QSqlQueryModel
{
public:
    SqlContactModel(QObject *parent = nullptr);
};

#endif // SQLCONTACTMODEL_H

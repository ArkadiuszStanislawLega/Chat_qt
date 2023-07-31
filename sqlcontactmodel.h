#ifndef SQLCONTACTMODEL_H
#define SQLCONTACTMODEL_H

#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include "dbmanager.h"

class SqlContactModel : public QSqlQueryModel{
public:
    Q_OBJECT
public:
    SqlContactModel(QObject *parent = nullptr);
};
#endif // SQLCONTACTMODEL_H

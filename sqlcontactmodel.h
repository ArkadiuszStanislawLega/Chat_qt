#ifndef SQLCONTACTMODEL_H
#define SQLCONTACTMODEL_H

#include "dbmanager.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>

class SqlContactModel : public QSqlQueryModel {
public:
  Q_OBJECT
public:
  SqlContactModel(QObject *parent = nullptr);
};
#endif // SQLCONTACTMODEL_H

#ifndef SQLCONVERSATIONMODEL_H
#define SQLCONVERSATIONMODEL_H

#include <QDateTime>
#include <QDebug>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>

#include "dbmanager.h"
#include "sqlcontactmodel.h"

class SqlConversationModel : public QSqlTableModel {
  Q_OBJECT
  Q_PROPERTY(QString recipient READ recipient WRITE set_recipient NOTIFY
                 recipient_change)
public:
  SqlConversationModel(QObject *parent = nullptr);

  QString recipient() const;
  void set_recipient(const QString &recipient);

  QVariant data(const QModelIndex &index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE void send_message(const QString &recipient,
                                const QString &message);

signals:
  void recipient_change();

private:
  QString _recipient;
};

#endif // SQLCONVERSATIONMODEL_H

#ifndef SQLMESSAGE_H
#define SQLMESSAGE_H

#include <QObject>

class SqlMessage : public QObject
{
  Q_OBJECT
      public:
               explicit SqlMessage(QObject *parent = nullptr);

signals:

};

#endif // SQLMESSAGE_H

#include "sqlconversationmodel.h"

static const char *CONVERSATION_TABLE_NAME = "Conversations";
static const char *AUTHOR_COLUMN = "author";
static const char *RECIPIENT_COLUMN = "recipient";
static const char *TIME_COLUMN = "timestamp";
static const char *MESSAGE_COLUMN = "message";

static void create_table(){
    if(QSqlDatabase::database().tables().contains(CONVERSATION_TABLE_NAME)){
        return;
    }

    QSqlQuery query;
    if(!query.exec(
            "CREATE TABLE IF NOT EXISTS 'Conversations' ("
            "'author' TEXT NOT NULL,"
            "'recipient' TEXT NOT NULL,"
            "'timestamp' TEXT NOT NULL,"
            "'message' TEXT NOT NULL,"
            "FOREIGN KEY('author') REFERENCES Contacts (name),"
            "FOREIGN KEY('recipient') REFERENCES Contacts (name)"
            ")")) {
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }

    query.exec("INSERT INTO Conversations VALUES('Me', 'Ernest Hemingway', '2016-01-07T14:36:06', 'Hello!')");
    query.exec("INSERT INTO Conversations VALUES('Ernest Hemingway', 'Me', '2016-01-07T14:36:16', 'Good afternoon.')");
    query.exec("INSERT INTO Conversations VALUES('Me', 'Albert Einstein', '2016-01-01T11:24:53', 'Hi!')");
    query.exec("INSERT INTO Conversations VALUES('Albert Einstein', 'Me', '2016-01-07T14:36:16', 'Good morning.')");
    query.exec("INSERT INTO Conversations VALUES('Hans Gude', 'Me', '2015-11-20T06:30:02', 'God morgen. Har du fått mitt maleri?')");
    query.exec("INSERT INTO Conversations VALUES('Me', 'Hans Gude', '2015-11-20T08:21:03', 'God morgen, Hans. Ja, det er veldig fint. Tusen takk! "
                   "Hvor mange timer har du brukt på den?')");
}

SqlConversationModel::SqlConversationModel(QObject *parent) : QSqlTableModel(parent){
    create_table();
    setTable(CONVERSATION_TABLE_NAME);
    setSort(2, Qt::DescendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QString SqlConversationModel::recipient() const {
    return this->_recipient;
}

void SqlConversationModel::set_recipient(const QString &recipient){
    if(recipient == this->_recipient){
        return;
    }

    this->_recipient = recipient;

    const QString filterString = QString::fromLatin1(
                                     "(recipient = '%1' AND author = 'Me') OR (recipient = 'Me' AND author = '%1')").arg(this->_recipient);
    setFilter(filterString);
    select();

    emit recipient_change();
}

QVariant SqlConversationModel::data(const QModelIndex &index, int role) const{
    if(role < Qt::UserRole){
        return QSqlTableModel::data(index, role);
    }
    const QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> SqlConversationModel::roleNames()const{
    QHash<int, QByteArray> names;
    names[Qt::UserRole] = AUTHOR_COLUMN;
    names[Qt::UserRole + 1] = RECIPIENT_COLUMN;
    names[Qt::UserRole + 2] = TIME_COLUMN;
    names[Qt::UserRole + 3] = MESSAGE_COLUMN;
    return names;
}

void SqlConversationModel::send_message(const QString &recipient, const QString &message){
    const QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);

    QSqlRecord n_record = record();
    n_record.setValue(AUTHOR_COLUMN, "Me");
    n_record.setValue(RECIPIENT_COLUMN, recipient);
    n_record.setValue(TIME_COLUMN, timestamp);
    n_record.setValue(MESSAGE_COLUMN, message);

    if(!insertRecord(rowCount(), n_record)){
        qWarning() << "Failed to send message: " << lastError().text();
        return;
    }

}

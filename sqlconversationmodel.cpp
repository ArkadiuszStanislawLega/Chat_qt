#include "sqlconversationmodel.h"


SqlConversationModel::SqlConversationModel(QObject *parent) : QSqlTableModel(parent){
    setTable(*CONVERSATION_TABLE_NAME);
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
    names[Qt::UserRole]  = AUTHOR_COLUMN->toLatin1();
    names[Qt::UserRole + 1] = RECIPIENT_COLUMN->toLatin1();
    names[Qt::UserRole + 2] = TIME_COLUMN->toLatin1();
    names[Qt::UserRole + 3] = MESSAGE_COLUMN->toLatin1();
    return names;
}

void SqlConversationModel::send_message(const QString &recipient, const QString &message){
    const QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);

    QSqlRecord n_record = record();
    n_record.setValue(*AUTHOR_COLUMN, "Me");
    n_record.setValue(*RECIPIENT_COLUMN, recipient);
    n_record.setValue(*TIME_COLUMN, timestamp);
    n_record.setValue(*MESSAGE_COLUMN, message);

    if(!insertRecord(rowCount(), n_record)){
        qWarning() << "Failed to send message: " << lastError().text();
        return;
    }

}

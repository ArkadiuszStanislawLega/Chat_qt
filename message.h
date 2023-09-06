#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDateTime>
#include <QObject>

#include "sqlmessage.h"

class SqlMessage;
class Message : public QObject {
	Q_OBJECT
private:
	int _id;
	int _contact_id;
	QString _authorId;
	QString _author_username;
	QString _text;
	QDateTime _sentTimestamp;

	Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged FINAL)
	Q_PROPERTY(int contactId READ getContactId WRITE setContactId NOTIFY ContactIdChanged FINAL)
	Q_PROPERTY(QString authorId READ getAuthorId WRITE setAuthorId NOTIFY authorIdChanged FINAL)
	Q_PROPERTY(QString authorUsername READ getAuthorUsername WRITE setAuthorUsername NOTIFY
				   AuthorUsernameChanged FINAL)
	Q_PROPERTY(QDateTime sentTimestamp READ getSentTimestamp WRITE setSentTimestamp NOTIFY
				   sentTimestampChanged FINAL)

	Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged FINAL)

public:
	explicit Message(QObject *parent = nullptr);

	int getId() const;
	void setId(int value);

	int getContactId() const;
	void setContactId(int value);

	QString getAuthorId() const;
	void setAuthorId(QString value);

	QString getAuthorUsername() const;
	void setAuthorUsername(const QString &value);

	QDateTime getSentTimestamp() const;
	void setSentTimestamp(const QDateTime &value);

	QString getText() const;
	void setText(const QString &value);

signals:
	void idChanged();
	void ContactIdChanged();
	void authorIdChanged();
	void AuthorUsernameChanged();
	void sentTimestampChanged();
	void textChanged();

public slots:
	bool sendMessage();
};

#endif // MESSAGE_H

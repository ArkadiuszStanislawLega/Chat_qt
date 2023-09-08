#include "user.h"
User::User(QObject *parent)
	: QObject{parent} {
	this->_id = "1";
	this->_username = "";
}
User::User(QString id, QString username, QVector<Contact *> contacts, QObject *parent)
	: QObject{parent} {
	this->_id = id;
	this->_username = username;
	this->_contacts = contacts;
}

/*!
 * \brief User::sqlUserToUserConverter converting SqlUser to user - user doesn't have password.
 * \param user Dwonloaded user properties from database.
 */
void User::sqlUserToUserConverter(SqlUser &user) {
	this->_id = QString::number(user.getId());
	this->_username = user.getUsername();
}

/*!
 * \brief User::addUserToDb Creating a user account. It creates a hash from the password provided as an argument and sends it to the server.
 * \param password Clear input of user password - not hashed.
 */
void User::addUserToDb(QString password) {
	// TODO: Move this to server.
	if (password.isEmpty()) {
		emit this->createdError();
		return;
	}

	password = QCryptographicHash::hash((password.toUtf8()), QCryptographicHash::Md5).toHex();

	SqlUser *sql = new SqlUser(this);
	sql->userToSqlUserConverter(*this);
	sql->setPassword(password);

	if (sql->createUser()) {
		this->setDbId(QString::number(sql->getId()));
		emit this->createdConfirmed();
		delete sql;
		return;
	}
	delete sql;
	emit this->createdError();
}

/*!
 * \brief User::isUserLogin Creating hash of user input and trying to authenticate user.
 * \param password User input password - not hashed.
 */
void User::isUserLogin(QString password) {
	password = QCryptographicHash::hash((password.toUtf8()), QCryptographicHash::Md5).toHex();

	if (this->auteticateUser(password))
		emit this->isLoginIn();
	else
		emit this->loginInFail();
}

/*!
 * \brief User::createContact Creating contact with user. Required user id.
 * \param userId User id whom contact will be created.
 */
void User::createContact(QString userId) {
	if (userId.isEmpty()) {
		emit this->failToCreateContact();
		return;
	}

	SqlUser *sql = new SqlUser(this);
	sql->setId(this->_id.toInt());

	if (sql->createContact(userId.toInt())) {
		delete sql;
		emit this->contactCreated();
		emit this->contactsChanged();
		return;
	}

	delete sql;
	emit this->failToCreateContact();
}

/*!
 * \brief User::auteticateUser Comparing created from user input hash with hash from database, after this set all user values.
 * \param password Hashed password.
 * \return True if the hashes match.
 */
bool User::auteticateUser(QString password) {
	if (password.isEmpty() || this->_id.isEmpty())
		return false;

	SqlUser *sql = new SqlUser(this);
	sql->userToSqlUserConverter(*this);

	if (!sql->isCredentialsCorrect(password)) {
		delete sql;
		return false;
	}

	if (sql->readUser()) {
		this->sqlUserToUserConverter(*sql);
		delete sql;
		return true;
	}

	delete sql;
	return false;
}

QString User::getUsername() {
	return this->_username;
}
void User::setUsername(QString username) {
	this->_username = username;
}

QString User::getDbId() {
	return this->_id;
}
void User::setDbId(QString id) {
	this->_id = id;
	emit this->idChanged();
}

/*!
 * \brief User::getContacts ask server to contacts connected with user id.
 * \return QVector with user contacts.
 */
QVector<Contact *> User::getContacts() {
	if (this->_id.isEmpty())
		return this->_contacts;

	SqlContact *sql = new SqlContact(this);
	sql->setUserId(this->_id.toInt());

	this->_contacts = sql->getUserContacts();
	return this->_contacts;
}
void User::setContacts(QVector<Contact *> contacts) {
	this->_contacts = contacts;
}

/*!
 * \brief User::sendMessage Send message to server if message not empty and user id is known.
 * \param text Text of the message.
 * \return True if message is added to database successfully.
 */
bool User::sendMessage(QString text) {
	if (text.isEmpty() || this->_id.isEmpty())
		return false;

	SqlMessage *sql = new SqlMessage(this);
	sql->setAuthorId(this->_id.toInt());
	sql->setSentTimestamp(QDateTime::currentDateTime());
	sql->setText(text);

	if (sql->createMessage()) {
		delete sql;
		emit this->messageSended();
		return true;
	}

	delete sql;
	emit this->failToSendMessage();
	return false;
}

#include "sqluser.h"

SqlUser::SqlUser(QObject *parent)
	: QObject{parent} {}

/*!
 * \brief SqlUser::getUserFromQuery 
 * \param query
 * \return 
 */
SqlUser *SqlUser::getUserFromQuery(QSqlQuery &query) {
	int id{}, id_column{}, username_column{}, password_column{};
	QString username{}, password{};

	id_column = query.record().indexOf(*ID_COLUMN_NAME);
	username_column = query.record().indexOf(*USERNAME_COLUMN_NAME);
	password_column = query.record().indexOf(*PASSWORD_COLUMN_NAME);

	id = query.value(id_column).toInt();
	username = query.value(username_column).toString();
	password = query.value(password_column).toString();

	SqlUser *user = new SqlUser(this);
	user->setId(id);
	user->setUsername(username);
	user->setPassword(password);

	return user;
}

/*!
 * \brief SqlUser::createUser creating user in database. 
 * \return True if creating user successful added to database.
 */
bool SqlUser::createUser() {
	QSqlQuery query;
	query.prepare("INSERT INTO " + *USERS_TABLE_NAME + "('" + *USERNAME_COLUMN_NAME + "','"
				  + *PASSWORD_COLUMN_NAME
				  + "')"
					" VALUES(:"
				  + *USERNAME_COLUMN_NAME + ",:" + *PASSWORD_COLUMN_NAME + ");");

	query.bindValue(":" + *USERNAME_COLUMN_NAME, this->_username);
	query.bindValue(":" + *PASSWORD_COLUMN_NAME, this->_password);

	if (!this->executeQuery(query))
		return false;

	this->_id = query.lastInsertId().toInt();
	return this->_id > 0;
}

/*!
 * \brief SqlUser::executeQuery Executing passed query.
 * \param query Sql query for execute.
 * \return True if executing finish successful.
 */
bool SqlUser::executeQuery(QSqlQuery &query) {
	qDebug() << "Sql User executing: " << query.lastQuery();
	if (!query.exec()) {
		qDebug() << query.lastError() << query.lastQuery();
		return false;
	}
	return true;
}

/*!
 * \brief SqlUser::isCredentialsCorrect Compare passed credential with data in database.
 * \param password Hashed password to compare.
 * \return True if user Id is in the database and hashes passed as argument and password from Database are same.
 */
bool SqlUser::isCredentialsCorrect(QString password) {
	if (password.isEmpty() || this->_id <= 0)
		return false;

	QSqlQuery query;
	query.prepare("SELECT * FROM " + *USERS_TABLE_NAME + " WHERE " + *ID_COLUMN_NAME
				  + " = :" + *ID_COLUMN_NAME + ";");

	query.bindValue(":" + *ID_COLUMN_NAME, this->_id);

	if (!this->executeQuery(query))
		return false;

	while (query.next()) {
		return this->getUserFromQuery(query)->getPassword() == password;
	}
	return false;
}

/*!
 * \brief SqlUser::readUser Reading user from database. Required set id before use.
 * \return True if data from database are loaded successfully.
 */
bool SqlUser::readUser() {
	QSqlQuery query;
	query.prepare("SELECT * FROM " + *USERS_TABLE_NAME + " WHERE " + *ID_COLUMN_NAME
				  + " = :" + *ID_COLUMN_NAME + ";");

	query.bindValue(":" + *ID_COLUMN_NAME, this->_id);

	if (!this->executeQuery(query))
		return false;

	while (query.next()) {
		SqlUser *user = this->getUserFromQuery(query);
		if (user) {
			this->_id = user->getId();
			this->_username = user->getUsername();
			this->_password = user->getPassword();
			delete (user);
			return true;
		}
	}

	return false;
}

bool SqlUser::updateUser() {
	return false;
}
bool SqlUser::deleteUser() {
	return false;
}

int SqlUser::getId() {
	return this->_id;
}
void SqlUser::setId(int value) {
	this->_id = value;
}

QString SqlUser::getUsername() {
	return this->_username;
}
void SqlUser::setUsername(QString value) {
	this->_username = value;
}

QString SqlUser::getPassword() {
	return this->_password;
}
void SqlUser::setPassword(QString value) {
	this->_password = value;
}

QDateTime SqlUser::getOccupied() {
	return this->_occupied;
}
void SqlUser::setOccupied(QDateTime value) {
	this->_occupied = value;
}

QDateTime SqlUser::getLastActivity() {
	return this->_last_activity;
}
void SqlUser::setLastActivity(QDateTime value) {
	this->_last_activity = value;
}

/*!
 * \brief SqlUser::userToSqlUserConverter Convert User Class to SqlUser Class.
 * \param user Data from User Class to convert to SqlUser.
 */
void SqlUser::userToSqlUserConverter(User &user) {
	this->_id = user.getDbId().toInt();
	this->_username = user.getUsername();
	this->_password = "";
}

/*!
 * \brief SqlUser::createContact Creating contact in database. Required set id.
 * \param contact_id Contact to whom users should be connected.
 * \return True if connection between users successfully created.
 */
bool SqlUser::createContact(int contact_id) {
	if (this->_id <= 0)
		return false;

	if (contact_id <= 0)
		return false;

	SqlContact *contact = new SqlContact(this);
	contact->setCreatedTimestamp(QDateTime::currentDateTime());
	contact->setUserId(this->_id);
	if (contact->connectUsersWithContact(this->_id, contact_id)) {
		return true;
	}

	return false;
}

/*!
 * \brief SqlUser::removeContact Removing contact between users. Cascade with messages. Required set user Id before use.
 * \param user_id User id in database with whom contact should be remove.
 * \return True if removing contact successfuly finished.
 */
bool SqlUser::removeContact(int user_id) {
	if (user_id <= 0)
		return false;

	SqlContact *contact = new SqlContact(this);
	contact->setUserId(this->_id);

	if (!contact->deleteContact()) {
		contact->setUserId(user_id);
		return contact->deleteContact();
	}

	return true;
}

/*!
 * \brief SqlUser::getContacts Getting list of contacts connected with user. Required set user Id before use.
 * \return List of contacts connected with user.
 */
QVector<Contact *> SqlUser::getContacts() {
	qDebug() << "SQL user get contacts: " << this->_id;
	if (this->_id <= 0)
		return {};

	SqlContact *sql = new SqlContact(this);
	sql->setUserId(this->_id);
	return sql->getUserContacts();
}

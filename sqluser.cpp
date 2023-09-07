#include "sqluser.h"

SqlUser::SqlUser(QObject *parent)
	: QObject{parent} {}

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

bool SqlUser::isCredentialsCorrect(int id, QString password) {
  if (password.isEmpty())
	  return false;

  if (id <= 0)
	  return false;

  QSqlQuery query;
  query.prepare("SELECT * FROM " + *USERS_TABLE_NAME + " WHERE " + *ID_COLUMN_NAME
				+ " = :" + *ID_COLUMN_NAME + ";");

  query.bindValue(":" + *ID_COLUMN_NAME, this->_id);

  if (!this->executeQuery(query))
	  return false;

  qDebug() << this->_id << this->_username << this->_password;

  while (query.next()) {
	  return this->getUserFromQuery(query)->getPassword() == password;
  }
  return false;
}

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

bool SqlUser::updateUser() { return false; }
bool SqlUser::deleteUser() { return false; }

bool SqlUser::sendMessage() { return false;
}

int SqlUser::getId() { return this->_id; }
void SqlUser::setId(int value) { this->_id = value; }

QString SqlUser::getUsername() { return this->_username; }
void SqlUser::setUsername(QString value) { this->_username = value; }

QString SqlUser::getPassword() { return this->_password; }
void SqlUser::setPassword(QString value) { this->_password = value; }

QDateTime SqlUser::getOccupied() { return this->_occupied; }
void SqlUser::setOccupied(QDateTime value) { this->_occupied = value; }

QDateTime SqlUser::getLastActivity() { return this->_last_activity; }
void SqlUser::setLastActivity(QDateTime value) { this->_last_activity = value; }

void SqlUser::userToSqlUserConverter(User &user) {
  this->_id = user.getDbId().toInt();
  this->_username = user.getUsername();
  this->_password = "";
}

bool SqlUser::createContact(int contact_id) {
  if (contact_id <= 0)
    return false;

  SqlContact *contact = new SqlContact(this);
  contact->setCreatedTimestamp(QDateTime::currentDateTime());
  contact->setUserId(this->_id);
  return contact->connectUsersWithContact(this->_id, contact_id);
}

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

QVector<Contact *> SqlUser::getContacts() {
  SqlContact *sql= new SqlContact(this);
  sql->setUserId(this->_id);
  return sql->getUserContacts();
}

bool SqlUser::executeQuery(QSqlQuery &query) {
  qDebug() << "Sql User executing: " << query.lastQuery();
  if (!query.exec()) {
	qDebug() << query.lastError() << query.lastQuery();
	return false;
  }
  return true;
}

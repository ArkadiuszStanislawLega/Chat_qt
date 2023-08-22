#include "sqluser.h"

SqlUser::SqlUser(QObject *parent) : QObject{parent} {}

SqlUser *SqlUser::getUserByPasswordAndUsername(QString username,
                                               QString password) {
  QSqlQuery query;
  QString cmd = "SELECT * FROM " + *USERS_TABLE_NAME + " WHERE " +
                *USERNAME_COLUMN_NAME + " = :" + *USERNAME_COLUMN_NAME +
                " AND " + *PASSWORD_COLUMN_NAME +
                " = :" + *PASSWORD_COLUMN_NAME + " LIMIT 1;";

  query.prepare(cmd);
  query.bindValue(":" + *USERNAME_COLUMN_NAME, username);
  query.bindValue(":" + *PASSWORD_COLUMN_NAME, password);
  if (!query.exec()) {
    qDebug() << query.lastError() << query.lastQuery();

    return nullptr;
  }

  while (query.next()) {
    int id, id_column, username_column, password_column;
    QString username, password;

    id_column = query.record().indexOf(*ID_COLUMN_NAME);
    username_column = query.record().indexOf(*USERNAME_COLUMN_NAME);
    password_column = query.record().indexOf(*PASSWORD_COLUMN_NAME);

    id = query.value(id_column).toInt();
    username = query.value(username_column).toString();
    password = query.value(password_column).toString();

    SqlUser *user = new SqlUser();
    user->setId(id);
    user->setUsername(username);
    user->setPassword(password);

    return user;
  }
  return nullptr;
}

bool SqlUser::createUser() {
  QSqlQuery query;
  QString cmd = "INSERT INTO " + *USERS_TABLE_NAME + "('" +
                *USERNAME_COLUMN_NAME + "','" + *PASSWORD_COLUMN_NAME +
                "')"
                " VALUES(:" +
                *USERNAME_COLUMN_NAME + ",:" + *PASSWORD_COLUMN_NAME + ");";

  query.prepare(cmd);
  query.bindValue(":" + *USERNAME_COLUMN_NAME, this->_username);
  query.bindValue(":" + *PASSWORD_COLUMN_NAME, this->_password);

  if (!query.exec()) {
    qDebug() << query.lastError() << query.lastQuery();
    return false;
  }

  return this->isAddingUserComplieted();
}

bool SqlUser::isAddingUserComplieted() {
  SqlUser *user =
      SqlUser::getUserByPasswordAndUsername(this->_username, this->_password);
  if (user->getUsername() == this->_username &&
      user->getPassword() == this->_password) {

    this->_id = user->getId();
    delete (user);
    return true;
  }
  delete (user);
  return false;
}

bool SqlUser::isCredentialsCorrect(int id, QString password) {
  if (password.isEmpty())
    return false;
  if (id <= 0)
    return false;

  QSqlQuery query;
  QString cmd = "SELECT " + *ID_COLUMN_NAME + ", " + *PASSWORD_COLUMN_NAME +
                " FROM " + *USERS_TABLE_NAME + " WHERE " + *ID_COLUMN_NAME +
                " = :" + *ID_COLUMN_NAME + ";";

  query.prepare(cmd);
  query.bindValue(":" + *ID_COLUMN_NAME, this->_id);

  if (!query.exec()) {
    qDebug() << query.lastError() << query.lastQuery();
    return false;
  }

  while (query.next()) {
    int id_column{}, password_column{};

    id_column = query.record().indexOf(*ID_COLUMN_NAME);
    password_column = query.record().indexOf(*PASSWORD_COLUMN_NAME);

    this->_id = query.value(id_column).toInt();
    this->_password = query.value(password_column).toString();
  }

  return password == this->_password;
}

bool SqlUser::readUser() {

  QSqlQuery query;
  QString cmd = "SELECT * FROM " + *USERS_TABLE_NAME + " WHERE " +
                *ID_COLUMN_NAME + " = :" + *ID_COLUMN_NAME + ";";

  query.prepare(cmd);
  query.bindValue(":" + *ID_COLUMN_NAME, this->_id);
  if (!query.exec()) {
    qDebug() << query.lastError() << query.lastQuery();
    return false;
  }

  while (query.next()) {
    int id_column{}, username_column{}, password_column{};

    id_column = query.record().indexOf(*ID_COLUMN_NAME);
    username_column = query.record().indexOf(*USERNAME_COLUMN_NAME);
    password_column = query.record().indexOf(*PASSWORD_COLUMN_NAME);

    this->_id = query.value(id_column).toInt();
    this->_username = query.value(username_column).toString();
    this->_password = query.value(password_column).toString();

    return true;
  }
  return false;
}

bool SqlUser::updateUser() { return false; }
bool SqlUser::deleteUser() { return false; }

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

bool SqlUser::createContact(int contact_id)
{
  QSqlQuery query;
  query.prepare("INSERT INTO " + *CONTACTS_TABLE_NAME + "('" + *ID_OWNER_COLUMN_NAME + "','"
                + *ID_USER_COLUMN_NAME + "','" + *CREATED_DATE_COLUMN_NAME + "')"
                + " VALUES (:" + *ID_OWNER_COLUMN_NAME + ",:" + *ID_USER_COLUMN_NAME
                + ",:" + *CREATED_DATE_COLUMN_NAME + ");");

  query.bindValue(":" + *ID_OWNER_COLUMN_NAME, this->_id);
  query.bindValue(":" + *ID_USER_COLUMN_NAME, contact_id);
  query.bindValue(":" + *CREATED_DATE_COLUMN_NAME, QDateTime::currentDateTime());
  if (query.exec())
    return true;

  qDebug() << query.lastError() << query.lastQuery();
  return false;
}

bool SqlUser::removeContact(int contact)
{
  return false;
}

QVector<Contact *> SqlUser::getContacts()
{
  QSqlQuery query;
  //SELECT Contacts.id, owner_id, user_id, created_date, username
  //FROM Contacts INNER JOIN Users ON Users.id = Contacts.owner_id
  //                                                where owner_id = 1 ;
  query.prepare("SELECT " + *ID_USER_COLUMN_NAME + ", " + *CREATED_DATE_COLUMN_NAME + ", "
                + *USERNAME_COLUMN_NAME + " FROM " + *CONTACTS_TABLE_NAME + " INNER JOIN "
                + *USERS_TABLE_NAME + " ON " + *USERS_TABLE_NAME + "." + *ID_COLUMN_NAME + " = "
                + *CONTACTS_TABLE_NAME + "." + *ID_USER_COLUMN_NAME + " WHERE "
                + *ID_OWNER_COLUMN_NAME + " = :" + *ID_OWNER_COLUMN_NAME + ";");

  query.bindValue(":" + *ID_OWNER_COLUMN_NAME, this->_id);
  if (!query.exec()) {
    qDebug() << query.lastError() << query.lastQuery();
    return {};
  }

  QVector<Contact *> contacts;
  while (query.next()) {
    int id_user_column{}, created_date_column{}, username_column{};
    id_user_column = query.record().indexOf(*ID_USER_COLUMN_NAME);
    created_date_column = query.record().indexOf(*CREATED_DATE_COLUMN_NAME);
    username_column = query.record().indexOf(*USERNAME_COLUMN_NAME);

    QDateTime date = query.value(created_date_column).toDateTime();
    User *user = new User(this);
    user->setDbId(query.value(id_user_column).toString());
    user->setUsername(query.value(username_column).toString());

    qDebug() << user->getDbId() << user->getUsername();

    contacts.push_back(new Contact(this->_id, user, date));
  }

  return contacts;
}

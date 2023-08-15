#include "sqluser.h"

SqlUser::SqlUser(QObject *parent) : QObject{parent} {}

QString SqlUser::getNextId() {
  QSqlQuery query;
  query.prepare("SELECT MAX(" + *ID_COLUMN_NAME + ") from " +
                *USERS_TABLE_NAME + ";");
  if (query.exec()) {
    while (query.next()) {
      int db_next_id = query.value(0).toInt();
      db_next_id++;
      return QString::number(db_next_id);
    }
  }
  return "-1";
}

bool SqlUser::createUser() {
  QVector<QPair<QString, QString>> args = {
      {*ID_COLUMN_NAME, QString::number(this->_id)},
      {*USERNAME_COLUMN_NAME, this->_username},
      {*PASSWORD_COLUMN_NAME, this->_password}};
  return DbManager::create(*USERS_TABLE_NAME, args);
}

bool SqlUser::isCredentialsCorrect() {
  QString id = QString::number(this->_id), password{};

  QVector<QPair<QString, QString *>> args = {
      {*ID_COLUMN_NAME, &id},
      {*PASSWORD_COLUMN_NAME, &password},
  };

  if (!DbManager::read(*USERS_TABLE_NAME, args))
    return false;
  return password == this->_password;
}

bool SqlUser::readUser() {
  QString id = QString::number(this->_id);

  QVector<QPair<QString, QString *>> args = {
      {*ID_COLUMN_NAME, &id},
      {*USERNAME_COLUMN_NAME, &this->_username},
      {*PASSWORD_COLUMN_NAME, &this->_password},
  };

  this->_id = id.toInt();

  return DbManager::read(*USERS_TABLE_NAME, args);
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
  this->_password = user.getPassword();
}

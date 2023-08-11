#include "register.h"

Register::Register(QObject *parent)
    : QObject{parent}
{

}

QString Register::getPassword(){
    return this->_password;
}

void Register::setPassword(QString password){
    this->_password = password;
    qDebug() << "setPassword:" << password;
    emit this->created();
}

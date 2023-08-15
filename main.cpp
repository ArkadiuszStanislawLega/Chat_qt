#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCore>

#include "dbmanager.h"
#include "sqlcontactmodel.h"
#include "sqlconversationmodel.h"
#include "user.h"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  qmlRegisterType<SqlContactModel>("io.qt.chat.contact_model", 1, 0,
                                   "SqlContactModel");
  qmlRegisterType<SqlConversationModel>("io.qt.chat.conversation_model", 1, 0,
                                        "SqlConversationModel");
  qmlRegisterType<User>("io.qt.chat.user", 1, 0, "User");

  DbManager(nullptr);

  QQmlApplicationEngine engine;
  const QUrl url(u"qrc:/Chat_qt/Main.qml"_qs);
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCore>

#include "sqlcontactmodel.h"
#include "sqlconversationmodel.h"
#include "dbmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SqlContactModel>("io.qt.chat", 1, 0, "SqlContactModel");
    qmlRegisterType<SqlConversationModel>("io.qt.chat", 1, 0, "SqlConversationModel");

    DbManager(nullptr);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Chat_qt/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
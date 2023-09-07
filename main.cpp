#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCore>

#include "dbmanager.h"
#include "user.h"
#include "message.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<User>("com.iam_code.chat.user", 1, 0, "User");
    qmlRegisterType<Contact>("com.iam_code.chat.contact", 1, 0, "Contact");
    qmlRegisterType<Message>("com.iam_code.chat.message", 1, 0, "Message");

    DbManager(nullptr);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Chat_qt/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

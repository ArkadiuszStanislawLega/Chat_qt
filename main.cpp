#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCore>

#include "sqlcontactmodel.h"
#include "sqlconversationmodel.h"

static void connect_database(){
    QSqlDatabase database = QSqlDatabase::database();
    if(!database.isValid()){
        database = QSqlDatabase::addDatabase("QSQLITE");
        if(!database.isValid()){
            qFatal("Cannot add database: %s", qPrintable(database.lastError().text()));
        }
    }

    const QDir write_directory = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if(!write_directory.mkpath(".")){
        qFatal("Failed to create writable directory at %s", qPrintable(write_directory.absolutePath()));
    }

    const QString file_name = write_directory.absolutePath() + "/chat_database.db";

    database.setDatabaseName(file_name);
    if(!database.open()){
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
        QFile::remove(file_name);
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SqlContactModel>("io.qt.chat", 1, 0, "SqlContactModel");
    qmlRegisterType<SqlConversationModel>("io.qt.chat", 1, 0, "SqlConversationModel");

    connect_database();

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Chat_qt/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

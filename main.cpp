#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QApplication>

#include "appengine.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    AppEngine appEngine;
    engine.rootContext()->setContextProperty(QStringLiteral("appengine"),&appEngine);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    if(argv[2] != nullptr){
        if(argv[1] == QStringLiteral("-f")){
            appEngine.showPathToImage(argv[2]);
        }
        if(argv[1] == QStringLiteral("-a")){
            QString pathPwd = "";
            QString command = "pwd > "+QDir::homePath()+"/pwd.txt";
            qDebug()<<command;
            QByteArray comm = command.toUtf8();
            system(comm);
            QFile pwd("pwd.txt");
            if ((pwd.exists())&&(pwd.open(QIODevice::ReadOnly)))
            {
                pathPwd = pwd.readLine(0);
                pwd.close();
            }
            pathPwd.remove(0,1);
            pathPwd.chop(1);
            appEngine.showPathToImage(pathPwd+"/"+argv[2]);
        }
    }


    return app.exec();
}

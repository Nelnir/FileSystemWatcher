#include <QGuiApplication>
#include <QQmlApplicationEngine>


#include "controller.h"
#include "eventtablemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Controller>("FSW.Controller", 1, 0, "Controller");
    qmlRegisterType<EventTableModel>("FSW.EventModel", 1, 0, "EventModel");


    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/FileSystemWatcher/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

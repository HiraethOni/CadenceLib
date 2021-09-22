#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Xlogger.h"
#include "databasectrl.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    int param = 1;

    XLOG_TRACE("this is trace log record, param: {}", ++param); // int type param is ok
    XLOG_DEBUG("this is debug log record, param: {}", ++param);
    XLOG_INFO("this is info log record, param: {}", ++param);
    XLOG_WARN("this is warn log record, param: {}", double(++param)); // double type param is ok
    XLOG_ERROR("this is error log record, param: {}", std::to_string(++param)); // string type param
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<CDatabaseCtrl>("com.hmqs.sqlqml", 1, 0, "DatabaseCtrl");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

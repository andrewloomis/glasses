#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <glasses.h>

int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Glasses glasses(app);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("gestureManager", glasses.getGestureManager().get());
    engine.rootContext()->setContextProperty("timeManager", glasses.getTimeManager().get());
    engine.rootContext()->setContextProperty("smsManager", glasses.getSmsManager().get());
    engine.rootContext()->setContextProperty("authenticationManager", glasses.getAuthenticationManager().get());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

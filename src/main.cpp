#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <glasses.h>

int main(int argc, char *argv[])
{


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Glasses glasses(app);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("manager", glasses.getSwipeManager());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

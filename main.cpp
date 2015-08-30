#include "CountdownTimer.h"

#include <QtQml>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setApplicationName("qTimer");
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("Andrey Kazantsev");
    QApplication::setOrganizationDomain("akazantsev.pp.ua");

    qmlRegisterType<CountdownTimer>("org.akazantsev", 1, 0, "CountdownTimer");

    QQmlEngine *engine = new QQmlEngine;
    QQmlComponent component(engine, QUrl("qrc:/main.qml"));

    auto window = qobject_cast<QWindow*>(component.create());
    if (window)
        window->setIcon(QIcon(":/icons/app.png"));

    qDebug() << component.errors();

    return app.exec();
}

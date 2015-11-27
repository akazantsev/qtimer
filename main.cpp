#include <cstdio>

#include <QtQml>
#include <QtWidgets>

#include "CircularProgress.h"
#include "CountdownTimer.h"
#include "Notification.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setApplicationName("qTimer");
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("Andrey Kazantsev");
    QApplication::setOrganizationDomain("akazantsev.pp.ua");

    qmlRegisterType<CircularProgress>("org.akazantsev", 1, 0, "CircularProgress");
    qmlRegisterType<CountdownTimer>("org.akazantsev", 1, 0, "CountdownTimer");
    qmlRegisterType<Notification>("org.akazantsev", 1, 0, "Notification");

    QQmlEngine *engine = new QQmlEngine;
    QQmlComponent component(engine, QUrl("qrc:/main.qml"));

    QIcon appIcon = QIcon(":/icons/app.png");
    auto window = qobject_cast<QWindow*>(component.create());
    if (window)
        window->setIcon(appIcon);

    if(component.isError())
    {
        QTextStream out(stdout);

        for (const auto &err : component.errors())
        {
            out << err.toString() << endl;
        }
    }

    return app.exec();
}

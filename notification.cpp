#include <QtWidgets>

#include "notification.h"
#include "dbusimage.h"

Notification::Notification(QObject *parent)
    : QObject(parent), m_timeout(0)
{
    iface = new org::freedesktop::Notifications(
                "org.freedesktop.Notifications", "/org/freedesktop/Notifications",
                QDBusConnection::sessionBus());
    connect(iface, SIGNAL(ActionInvoked(uint,QString)),
            this, SLOT(actionHandler(uint,QString)));
}

Notification::~Notification()
{

}

void Notification::actionHandler(uint, const QString &action)
{
    emit actionInvoked(action);
}

void Notification::show() const
{
    iface->Notify(qApp->applicationName(), 0, "", title, body, actions, hints,
                  m_timeout);
}

void Notification::addAction(const QString &id, const QString &text)
{
    Q_ASSERT(!id.isEmpty());
    Q_ASSERT(!text.isEmpty());

    actions << id << text;
}

void Notification::setIcon(const QIcon &icon)
{
    Q_ASSERT(!icon.isNull());

    QPixmap pixmap = icon.pixmap(64, 64);
    DBusImage dbusImage(pixmap.toImage());

    hints.insert("image_data", QVariant::fromValue(dbusImage));
}

void Notification::setText(const QString &text)
{
    Q_ASSERT(!text.isNull());

    title = text;
}

void Notification::setTimeout(int t)
{
    m_timeout = t;
}

void Notification::setBodyText(const QString &text)
{
    Q_ASSERT(!text.isNull());

    body = text;
}


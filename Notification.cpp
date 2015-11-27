#include <QtWidgets>

#include "Notification.h"
#include "dbusimage.h"

Notification::Notification(QObject *parent)
    : QObject(parent), m_timeout(0)
{
    iface = new org::freedesktop::Notifications(
                "org.freedesktop.Notifications",
                "/org/freedesktop/Notifications",
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
    iface->Notify(qApp->applicationName(), 0, "", m_text, m_bodyText,
                  actions, hints, m_timeout);
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

int Notification::timeout() const
{
    return m_timeout;
}

void Notification::setTimeout(int timeout)
{
    if (m_timeout == timeout)
        return;

    m_timeout = timeout;
    emit timeoutChanged(timeout);
}

QString Notification::text() const
{
    return m_text;
}

void Notification::setText(const QString &text)
{
    Q_ASSERT(!text.isNull());

    if (m_text == text)
        return;

    m_text = text;
    emit textChanged(text);
}

QString Notification::bodyText() const
{
    return m_bodyText;
}

void Notification::setBodyText(const QString &bodyText)
{
    Q_ASSERT(!bodyText.isNull());

    if (m_bodyText == bodyText)
        return;

    m_bodyText = bodyText;
    emit bodyTextChanged(bodyText);
}


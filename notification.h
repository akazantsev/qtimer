#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QMainWindow>
#include <QStringList>
#include <QVariantHash>

#include "notifications_interface.h"

class Notification : public QObject
{
    Q_OBJECT

public:
    Notification(QObject *parent = nullptr);
    ~Notification();

    void show() const;
    void addAction(const QString &id, const QString &text);
    void setIcon(const QIcon &icon);
    void setText(const QString &text);
    void setTimeout(int t);
    void setBodyText(const QString &text);

signals:
    void actionInvoked(const QString &id);

private slots:
    void actionHandler(uint id, const QString &action);

private:
    int m_timeout;
    QString title;
    QString body;
    QVariantHash hints;
    QStringList actions;
    org::freedesktop::Notifications *iface;
};

#endif // NOTIFICATION_H

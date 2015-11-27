#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QMainWindow>
#include <QStringList>
#include <QVariantHash>

#include "notifications_interface.h"

class Notification : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)
    Q_PROPERTY(QString bodyText READ bodyText WRITE setBodyText NOTIFY bodyTextChanged)

public:
    Notification(QObject *parent = nullptr);
    ~Notification();

    Q_INVOKABLE void show() const;
    void addAction(const QString &id, const QString &text);
    void setIcon(const QIcon &icon);

    int timeout() const;
    void setTimeout(int timeout);

    QString text() const;
    void setText(const QString &text);

    QString bodyText() const;
    void setBodyText(const QString &newBodyText);

signals:
    void actionInvoked(const QString &id);

    void textChanged(const QString &newText);
    void timeoutChanged(int timeout);
    void bodyTextChanged(const QString &newBodyText);

private slots:
    void actionHandler(uint, const QString &action);

private:
    int m_timeout;
    QString m_text;
    QString m_bodyText;
    QVariantHash hints;
    QStringList actions;
    org::freedesktop::Notifications *iface;
};

#endif // NOTIFICATION_H

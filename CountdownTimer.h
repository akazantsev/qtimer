#pragma once

#include <QObject>

class CountdownTimer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(int timeLeft READ timeLeft NOTIFY timeLeftChanged)

public:
    explicit CountdownTimer(QObject *parent = 0);

    int time() const;
    void setTime(int newTime);
    int timeLeft() const;

    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void reset();

signals:
    void timeChanged(int newTime);
    void timeLeftChanged(int newTimeLeft);

private:
    int m_time;
};


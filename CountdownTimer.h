#pragma once

#include <QObject>
#include <QTime>

class CountdownTimer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int duration READ duration WRITE setDuration
               NOTIFY durationChanged)
    Q_PROPERTY(int timeLeft READ timeLeft NOTIFY timeLeftChanged)

public:
    explicit CountdownTimer(QObject *parent = 0);

    int duration() const;
    void setDuration(int newDuration);
    int timeLeft() const;

    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void reset();

signals:
    void durationChanged(int newDuration);
    void timeLeftChanged(int newTimeLeft);
    void timeOut();

protected:
    void timerEvent(QTimerEvent *);

private:
    int m_duration;
    int m_timeLeft;
    int m_timerId;
    QTime m_startTime;

    bool isRunning() const;
    void setTimeLeft(int newTimeLeft);
    void stopTimer();
};


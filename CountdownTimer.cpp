#include <QTime>

#include "CountdownTimer.h"

CountdownTimer::CountdownTimer(QObject *parent) :
    QObject(parent), m_duration(0), m_timeLeft(0), m_timerId(0)
{

}

int CountdownTimer::duration() const
{
    return m_duration;
}

void CountdownTimer::setDuration(int newDuration)
{
    if (m_duration == newDuration)
        return;

    m_duration = newDuration;
    setTimeLeft(m_duration * 1000); // converting to mSec
    emit durationChanged(newDuration);
}

int CountdownTimer::timeLeft() const
{
    return m_timeLeft;
}

void CountdownTimer::setTimeLeft(int newTimeLeft)
{
    if (m_timeLeft == newTimeLeft)
        return;

    m_timeLeft = newTimeLeft;
    emit timeLeftChanged(newTimeLeft);
}

bool CountdownTimer::running() const
{
    return m_timerId != 0;
}

void CountdownTimer::setRunning(bool newRunning)
{
    if (running() == newRunning)
        return;

    if (newRunning)
        start();
    else
        stop();

    emit runningChanged(newRunning);
}

void CountdownTimer::start()
{
    m_timerId = startTimer(10);
    m_startTime = QTime::currentTime();
    m_startTime.start();
}

void CountdownTimer::stop()
{
    killTimer(m_timerId);
    m_timerId = 0;
}

void CountdownTimer::reset()
{
    stop();
    setTimeLeft(m_duration * 1000);
}

void CountdownTimer::timerEvent(QTimerEvent *)
{
    int newTimeLeft = timeLeft() - m_startTime.restart();

    if (newTimeLeft <= 0)
    {
        newTimeLeft = 0;
        stop();
        emit timeOut();
    }

    setTimeLeft(newTimeLeft);
}

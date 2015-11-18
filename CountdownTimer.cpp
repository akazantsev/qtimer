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
    if (m_duration != newDuration)
    {
        m_duration = newDuration;
        setTimeLeft(m_duration * 1000); // converting to mSec
        emit durationChanged(m_duration);
    }
}

int CountdownTimer::timeLeft() const
{
    return m_timeLeft;
}

void CountdownTimer::start()
{
    m_timerId = startTimer(25);
    m_startTime = QTime::currentTime();
    m_startTime.start();
}

void CountdownTimer::pause()
{
    stopTimer();
}

void CountdownTimer::reset()
{
    stopTimer();
    setTimeLeft(m_duration * 1000);
}

void CountdownTimer::timerEvent(QTimerEvent *)
{
    int newTimeLeft = timeLeft() - m_startTime.restart();

    if (newTimeLeft <= 0)
    {
        newTimeLeft = 0;
        stopTimer();
        emit timeOut();
    }

    setTimeLeft(newTimeLeft);
}

bool CountdownTimer::isRunning() const
{
    return m_timerId != 0;
}

void CountdownTimer::setTimeLeft(int newTimeLeft)
{
    if (m_timeLeft != newTimeLeft)
    {
        m_timeLeft = newTimeLeft;
        emit timeLeftChanged(m_timeLeft);
    }
}

void CountdownTimer::stopTimer()
{
    killTimer(m_timerId);
    m_timerId = 0;
}

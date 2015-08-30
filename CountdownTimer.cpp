#include "CountdownTimer.h"

CountdownTimer::CountdownTimer(QObject *parent) :
    QObject(parent), m_duration(0)
{

}

int CountdownTimer::duration() const
{
    return m_duration;
}

void CountdownTimer::setDuration(int newDuration)
{
    if (newDuration != m_duration)
    {
        m_duration = newDuration;
        emit durationChanged(newDuration);
    }
}

int CountdownTimer::timeLeft() const
{
    return 0;
}

void CountdownTimer::start()
{

}

void CountdownTimer::pause()
{

}

void CountdownTimer::reset()
{

}

#include "CountdownTimer.h"

CountdownTimer::CountdownTimer(QObject *parent) :
    QObject(parent)
{

}

int CountdownTimer::time() const
{
    return m_time;
}

void CountdownTimer::setTime(int newTime)
{
    if (newTime != m_time)
    {
        m_time = newTime;
        emit timeChanged(newTime);
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

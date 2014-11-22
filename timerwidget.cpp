#include <QtWidgets>

#include "timerwidget.h"

TimerWidget::TimerWidget(QWidget *parent) :
    QWidget(parent), alarmTimer(0), uiTimer(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_duration = 1 * 6;
    alarmDuration = 60;

    mLabel = new QLabel;
    mSuffixLabel = new QLabel(tr("<sub>m</sub>"));
    sLabel = new QLabel;
    sSuffixLabel = new QLabel(tr("<sub>s</sub>"));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addStretch();
    layout->addWidget(mLabel);
    layout->addWidget(mSuffixLabel);
    layout->addSpacing(20);
    layout->addWidget(sLabel);
    layout->addWidget(sSuffixLabel);
    layout->addStretch();
    setLayout(layout);

    updateTimer();
}

bool TimerWidget::isRunning() const
{
    return uiTimer != 0;
}

void TimerWidget::setAlarmDuration(int s)
{
    Q_ASSERT(s >= 0);

    alarmDuration = s;
}

int TimerWidget::position() const
{
    return m_position;
}

void TimerWidget::setPosition(int p)
{
    m_position = p;
}

int TimerWidget::duration() const
{
    return m_duration;
}

void TimerWidget::setDuration(int s)
{
    const int min = 0;
    const int max = 60 * 60; // one hour
    m_duration = (s < min ? min : (s > max ? max : s));

    reset();
}

QColor TimerWidget::color() const
{
    return palette().color(QPalette::WindowText);
}

void TimerWidget::setColor(QColor c)
{
    QPalette p = palette();
    p.setColor(QPalette::WindowText, c);
    setPalette(p);
}

// Public slots

void TimerWidget::start()
{
    startTime.start();
    uiTimer = startTimer(300);
}

void TimerWidget::stop()
{
    if (!isRunning())
        return;

    m_position = left();
    killTimer(uiTimer);
    uiTimer = 0;
}

void TimerWidget::deactivate()
{
    emit alarmDeactivated();
    killTimer(alarmTimer);
    alarmTimer = 0;
}

void TimerWidget::reset()
{
    stop();
    deactivate();
    m_position = m_duration;
    updateTimer();
}

// Protected

void TimerWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == uiTimer)
    {
        if (left() <= 0)
        {
            emit timeout();
            alarmTimer = startTimer(alarmDuration * 1000);
            stop();
        }

        updateTimer();
    } else if (event->timerId() == alarmTimer) {
        deactivate();
    }
}

void TimerWidget::wheelEvent(QWheelEvent *event)
{
    const int scrollUnit = 120;
    bool min = QRect(mLabel->pos(), mSuffixLabel->pos() +
                     mSuffixLabel->rect().bottomRight()).contains(event->pos());
    bool sec = QRect(sLabel->pos(), sSuffixLabel->pos() +
                     sSuffixLabel->rect().bottomRight()).contains(event->pos());
    static int step = 0;

    if (!isRunning() && (min || sec))
    {
        step += event->angleDelta().y();

        if (qAbs(step) >= scrollUnit)
        {
            int inc = step / scrollUnit;

            if (min)
            {
                inc *= 60;
            }

            setDuration(inc + m_position);
            step %= scrollUnit;
        }
    }

    event->ignore();
    return;
}

// Private

int TimerWidget::left() const
{
    int secsLeft = m_position;

    if (isRunning())
        secsLeft -= startTime.elapsed() / 1000;

    if (secsLeft < 0)
        return 0;

    return secsLeft;
}

void TimerWidget::updateTimer()
{
    const int secs = left();

    mLabel->setText(fmtTime(secs / 60));
    sLabel->setText(fmtTime(secs % 60));
}

QString TimerWidget::fmtTime(int s) const
{
    return QString("%1").arg(s, 2, 10, QChar('0'));
}

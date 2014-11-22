#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>

class QAbstractAnimation;
class QLabel;

class TimerWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit TimerWidget(QWidget *parent = 0);

    bool isRunning() const;
    void setAlarmDuration(int s);

    int position() const;
    void setPosition(int p);

    int duration() const;
    void setDuration(int s);

    QColor color() const;
    void setColor(QColor c);

signals:
    void timeout();
    void alarmDeactivated();

public slots:
    void start();
    void stop();
    void deactivate();
    void reset();

protected:
    void timerEvent(QTimerEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:

private:
    int m_position;
    int m_duration;
    int alarmDuration;

    int alarmTimer;
    int uiTimer;

    QTime startTime;

    QLabel *mLabel;
    QLabel *mSuffixLabel;
    QLabel *sLabel;
    QLabel *sSuffixLabel;

    void updateTimer();
    QString fmtTime(int s) const;
};

#endif // TIMERWIDGET_H

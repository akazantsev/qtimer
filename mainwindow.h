#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class Notification;
class QMediaPlayer;
class QPropertyAnimation;

class QStateMachine;
class QState;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void alarm();
    void deactivateAlarm();
    void notifAction(const QString &actionId);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

    void saveSettings();
    void restoreSettings();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    QIcon appIcon;
    Notification *timeoutNotif;
    QMediaPlayer *mediaPlayer;
    QPropertyAnimation *animation;
    QSystemTrayIcon *trayIcon;

    // State machine
    QStateMachine *stateMachine;
    QState *normalState;
    QState *pausedState;
    QState *runningState;
    QState *alarmState;

    void createAlarmAnimation();
    void createNotification();
    void createStateMachine();
    void createConnections();
};

#endif // MAINWINDOW_H

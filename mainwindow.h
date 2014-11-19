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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void alarm();
    void deactivateAlarm();
    void startStop();
    void reset();
    void notifAction(const QString &actionId);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;

    QIcon appIcon;
    Notification *timeoutNotif;
    QMediaPlayer *mediaPlayer;
    QPropertyAnimation *animation;
    QSystemTrayIcon *trayIcon;

    void start();
    void stop();
};

#endif // MAINWINDOW_H

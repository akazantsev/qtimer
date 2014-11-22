#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notification.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    appIcon = QIcon(":/icons/app.png");
    setWindowIcon(appIcon);
    resize(minimumSizeHint());
    setWindowTitle(QApplication::applicationName());

    QMediaPlaylist *playlist = new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist->addMedia(QUrl::fromLocalFile(QDir::currentPath() +
                                           "/../qtimer/sounds/alarm.ogg"));

    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setPlaylist(playlist);

    trayIcon = new QSystemTrayIcon(appIcon, this);
    trayIcon->show();

    createAlarmAnimation();
    createNotification();
    createStateMachine();
    createConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Private slots

void MainWindow::alarm()
{
    animation->setLoopCount(-1);
    animation->start();
    mediaPlayer->play();
    timeoutNotif->show();
}

void MainWindow::deactivateAlarm()
{
    animation->setLoopCount(1);
    mediaPlayer->stop();
}

void MainWindow::notifAction(const QString &actionId)
{
    if (actionId == "deactivate")
    {
        ui->timerWidget->deactivate();
    }
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        if (isVisible())
        {
            hide();
        } else {
            // ToDo: send bug report
            QPoint p = pos();
            move(0, 0);
            show();
            move(p);
        }
    }
}

void MainWindow::saveSettings()
{

}

void MainWindow::restoreSettings()
{

}

// Private

void MainWindow::createAlarmAnimation()
{
    animation = new QPropertyAnimation(ui->timerWidget, "color");
    animation->setDuration(1500);
    animation->setEasingCurve(QEasingCurve::OutInQuart);
    animation->setKeyValueAt(0.0, ui->timerWidget->color());
    animation->setKeyValueAt(0.5, QColor(200, 100, 100));
    animation->setKeyValueAt(1.0, ui->timerWidget->color());
}

void MainWindow::createNotification()
{
    timeoutNotif = new Notification(this);
    timeoutNotif->setIcon(appIcon);
    timeoutNotif->setText(tr("Timeout"));
    timeoutNotif->setBodyText(tr("Time expired"));
    timeoutNotif->setTimeout(5000);
    timeoutNotif->addAction("deactivate", tr("Deactivate"));
}

void MainWindow::createStateMachine()
{
    stateMachine = new QStateMachine;

    // Normal state
    normalState = new QState;
    normalState->assignProperty(ui->startStopButton, "enabled", true);

    normalState->assignProperty(ui->resetButton, "enabled", false);
    normalState->assignProperty(ui->resetButton, "icon",
                                QIcon::fromTheme("media-playback-stop"));
    normalState->assignProperty(ui->resetButton, "text", "&Reset");

    // Paused state
    pausedState = new QState;
    pausedState->assignProperty(ui->startStopButton, "text", "&Start");
    pausedState->assignProperty(ui->startStopButton, "icon",
                                QIcon::fromTheme("media-playback-start"));

    // Running state
    runningState = new QState;
    runningState->assignProperty(ui->startStopButton, "text", "&Pause");
    runningState->assignProperty(ui->startStopButton, "icon",
                                 QIcon::fromTheme("media-playback-pause"));

    runningState->assignProperty(ui->resetButton, "enabled", true);

    // Alarm state
    alarmState = new QState;
    alarmState->assignProperty(ui->startStopButton, "enabled", false);
    alarmState->assignProperty(ui->startStopButton, "text", "&Start");
    alarmState->assignProperty(ui->startStopButton, "icon",
                                QIcon::fromTheme("media-playback-start"));

    // ToDo: Change icon as well
    alarmState->assignProperty(ui->resetButton, "text", "&Disarm");

    // Transitions
    normalState->addTransition(ui->startStopButton, SIGNAL(clicked()), runningState);
    pausedState->addTransition(ui->startStopButton, SIGNAL(clicked()), runningState);
    pausedState->addTransition(ui->resetButton, SIGNAL(clicked()), normalState);
    runningState->addTransition(ui->startStopButton, SIGNAL(clicked()), pausedState);
    runningState->addTransition(ui->resetButton, SIGNAL(clicked()), normalState);
    runningState->addTransition(ui->timerWidget, SIGNAL(timeout()), alarmState);
    alarmState->addTransition(ui->resetButton, SIGNAL(clicked()), normalState);

    stateMachine->addState(normalState);
    stateMachine->addState(pausedState);
    stateMachine->addState(runningState);
    stateMachine->addState(alarmState);
    stateMachine->setInitialState(normalState);
    stateMachine->start();
}

void MainWindow::createConnections()
{
    connect(timeoutNotif, SIGNAL(actionInvoked(const QString &)),
            this, SLOT(notifAction(const QString &)));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    // State machine connections
    connect(normalState, SIGNAL(entered()), ui->timerWidget, SLOT(reset()));
    connect(runningState, SIGNAL(entered()), ui->timerWidget, SLOT(start()));
    connect(pausedState, SIGNAL(entered()), ui->timerWidget, SLOT(stop()));
    connect(alarmState, SIGNAL(entered()), this, SLOT(alarm()));
    connect(alarmState, SIGNAL(exited()), this, SLOT(deactivateAlarm()));
}


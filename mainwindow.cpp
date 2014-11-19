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

    ui->resetButton->setIcon(QIcon::fromTheme("media-playback-stop"));

    QMediaPlaylist *playlist = new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist->addMedia(QUrl::fromLocalFile(QDir::currentPath() + "/../qtimer/sounds/alarm.ogg"));

    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setPlaylist(playlist);

    trayIcon = new QSystemTrayIcon(appIcon, this);
    trayIcon->show();

    timeoutNotif = new Notification(this);
    timeoutNotif->setIcon(appIcon);
    timeoutNotif->setText(tr("Timeout"));
    timeoutNotif->setBodyText(tr("Time expired"));
    timeoutNotif->setTimeout(5000);
    timeoutNotif->addAction("deactivate", tr("Deactivate"));

    animation = new QPropertyAnimation(ui->timerWidget, "color");
    animation->setDuration(1500);
    animation->setEasingCurve(QEasingCurve::OutInQuart);
    animation->setKeyValueAt(0.0, ui->timerWidget->color());
    animation->setKeyValueAt(0.5, QColor(200, 100, 100));
    animation->setKeyValueAt(1.0, ui->timerWidget->color());

    connect(ui->timerWidget, SIGNAL(timeout()), this, SLOT(alarm()));
    connect(ui->timerWidget, SIGNAL(alarmDeactivated()),
            this, SLOT(deactivateAlarm()));
    connect(ui->startStopButton, SIGNAL(clicked()), this, SLOT(startStop()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(reset()));
    connect(timeoutNotif, SIGNAL(actionInvoked(const QString &)),
            this, SLOT(notifAction(const QString &)));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    stop();
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

void MainWindow::startStop()
{
    if (!ui->timerWidget->isRunning())
    {
        ui->resetButton->setEnabled(true);
        ui->timerWidget->start();
    } else {
        ui->timerWidget->stop();
    }
}

void MainWindow::reset()
{
    ui->timerWidget->reset();
    ui->resetButton->setEnabled(false);
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

// Private

void MainWindow::start()
{
    ui->timerWidget->start();
    ui->startStopButton->setIcon(QIcon::fromTheme("media-playback-pause"));
    ui->startStopButton->setText(tr("&Pause"));
    ui->resetButton->setEnabled(true);
}

void MainWindow::stop()
{
    ui->timerWidget->stop();
    ui->startStopButton->setIcon(QIcon::fromTheme("media-playback-start"));
    ui->startStopButton->setText(tr("&Start"));
}




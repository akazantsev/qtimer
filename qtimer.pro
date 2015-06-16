#-------------------------------------------------
#
# Project created by QtCreator 2014-09-28T10:51:37
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets qml quick

TARGET = qtimer
TEMPLATE = app
CONFIG += c++14

SOURCES += main.cpp \
        mainwindow.cpp \
    timerwidget.cpp

HEADERS  += mainwindow.h \
    timerwidget.h

linux-g++ {
    QT += dbus

    DBUS_INTERFACES += org.freedesktop.Notifications.xml

    SOURCES += dbusimage.cpp \
        notification.cpp

    HEADERS += dbusimage.h \
        notification.h
}

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc \
    qml.qrc

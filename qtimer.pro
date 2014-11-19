#-------------------------------------------------
#
# Project created by QtCreator 2014-09-28T10:51:37
#
#-------------------------------------------------

QT       += core gui dbus multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtimer
TEMPLATE = app
CONFIG += c++11

DBUS_INTERFACES += org.freedesktop.Notifications.xml

SOURCES += main.cpp\
        mainwindow.cpp \
    dbusimage.cpp \
    notification.cpp \
    timerwidget.cpp

HEADERS  += mainwindow.h \
    dbusimage.h \
    notification.h \
    timerwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

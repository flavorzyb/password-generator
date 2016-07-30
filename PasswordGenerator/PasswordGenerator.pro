#-------------------------------------------------
#
# Project created by QtCreator 2016-07-30T14:26:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PasswordGenerator
TEMPLATE = app


SOURCES += $$PWD/src/main.cpp\
        $$PWD/src/mainwindow.cpp

HEADERS  += $$PWD/src/mainwindow.h

macx {
    ICON = $$PWD/resources/icon/pg.icns
    QMAKE_INFO_PLIST = $$PWD/resources/Info.plist
}

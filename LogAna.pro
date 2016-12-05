#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T09:35:00
#
#-------------------------------------------------

QT       += core gui network ftp xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogAna
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    ftpdownloard.cpp \
    mainform.cpp \
    devmanger.cpp \
    atmpconfig.cpp \
    global.cpp

HEADERS  += \
    mainwindow.h \
    ftpdownloard.h \
    mainform.h \
    devmanger.h \
    atmpconfig.h \
    global.h

FORMS += \
    mainwindow.ui \
    mainform.ui \
    devmanger.ui \
    atmpconfig.ui

DISTFILES += \
    Res/dev.ini \
    Res/atmp.ini \
    Res/README.md

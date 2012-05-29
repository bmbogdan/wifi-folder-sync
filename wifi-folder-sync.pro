#-------------------------------------------------
#
# Project created by QtCreator 2012-05-28T14:12:53
#
#-------------------------------------------------

QT       += core gui network

TARGET = wifi-folder-sync
TEMPLATE = app


SOURCES += main.cpp\
        gui.cpp \
    mthread.cpp \
    directoryscanner.cpp \
    udp.cpp

HEADERS  += gui.h \
    mthread.h \
    directoryscanner.h \
    udp.h

FORMS    += gui.ui

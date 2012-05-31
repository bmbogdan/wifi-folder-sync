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
    filesystem/fileobject.cpp \
    filesystem/directoryscanner.cpp \
    filesystem/directoryparser.cpp \
    networking/udp.cpp \
    networking/slavemaster.cpp \
    networking/masterslave.cpp \
    filesystem/fileresolver.cpp \
    filesystem/directorybuilder.cpp

HEADERS  += gui.h \
    mthread.h \
    filesystem/fileobject.h \
    filesystem/directoryscanner.h \
    filesystem/directoryparser.h \
    networking/udp.h \
    networking/slavemaster.h \
    networking/masterslave.h \
    filesystem/fileresolver.h \
    filesystem/directorybuilder.h

FORMS    += gui.ui

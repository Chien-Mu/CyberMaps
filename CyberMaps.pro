#-------------------------------------------------
#
# Project created by QtCreator 2017-07-24T10:35:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CyberMaps
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mapsviewer.cpp \
    cyberglobal.cpp

HEADERS  += mainwindow.h \
    mapsviewer.h \
    cyberglobal.h

FORMS    += mainwindow.ui \
    mapsviewer.ui

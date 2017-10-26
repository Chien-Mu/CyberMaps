#-------------------------------------------------
#
# Project created by QtCreator 2017-07-24T10:35:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = CyberMaps
TEMPLATE = app
QMAKE_CXXFLAGS += -Wno-inconsistent-missing-override


SOURCES += main.cpp\
        mainwindow.cpp \
    mapsviewer.cpp \
    cyberglobal.cpp \
    datareader.cpp \
    multilateration.cpp \
    config.cpp \
    QCustomPlot/qcustomplot.cpp

HEADERS  += mainwindow.h \
    mapsviewer.h \
    cyberglobal.h \
    datareader.h \
    multilateration.h \
    config.h \
    QCustomPlot/qcustomplot.h

FORMS    += mainwindow.ui \
    mapsviewer.ui \
    config.ui

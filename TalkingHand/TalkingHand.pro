#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T09:41:42
#
#-------------------------------------------------

QT       += core gui\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TalkingHand
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Communication/client.cpp

HEADERS  += mainwindow.h \
    Communication/client.h \
    SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h \
    SistemasdeControle/src/primitiveLibs/LinAlg/matrix.hpp

FORMS    += mainwindow.ui

CONFIG += mobility
CONFIG += console

MOBILITY = 

RESOURCES += \
    res.qrc

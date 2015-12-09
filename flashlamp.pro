#-------------------------------------------------
#
# Project created by QtCreator 2015-12-08T17:36:09
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(qmqttlib/qmqtt.pri)

TARGET = flashlamp
TEMPLATE = app

SOURCES += main.cpp\
        flashlamp.cpp

HEADERS  += flashlamp.h

FORMS    += flashlamp.ui

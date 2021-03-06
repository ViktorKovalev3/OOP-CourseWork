#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T17:06:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseWork
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        GUI/mainwindow.cpp \
    Course/Engine.cpp \
    Course/Model.cpp \
    Course/Mechanic.cpp \
    Course/Statistic.cpp \
    Course/ExponentialDistribution.cpp \
    GUI/statisticGUI.cpp

HEADERS  += GUI/mainwindow.h \
    Course/Engine.h \
    Course/Model.h \
    Course/Mechanic.h \
    Course/Statistic.h \
    Course/ExponentialDistribution.h \
    GUI/statisticGUI.h

FORMS    += GUI/mainwindow.ui \
    GUI/statisticGUI.ui
CONFIG += c++14

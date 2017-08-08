#-------------------------------------------------
#
# Project created by QtCreator 2017-03-25T19:43:16
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Journal
TEMPLATE = app
CONFIG += console


SOURCES += main.cpp\
        mainwindow.cpp \
    paper.cpp \
    papermodel.cpp \
    tool.cpp \
    pentool.cpp \
    selecttool.cpp \
    texttool.cpp \
    textbox.cpp \
    paperlist.cpp

HEADERS  += mainwindow.h \
    paper.h \
    papermodel.h \
    tool.h \
    pentool.h \
    selecttool.h \
    texttool.h \
    textbox.h \
    paperlist.h \
    huge_dictionary.h

FORMS    += mainwindow.ui

DISTFILES += \
    README.md \
    uml.qmodel

RESOURCES += \
    assets.qrc

STATECHARTS +=

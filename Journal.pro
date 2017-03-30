#-------------------------------------------------
#
# Project created by QtCreator 2017-03-25T19:43:16
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Journal
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paper.cpp \
    selecttool.cpp \
    texttool.cpp \
    pentool.cpp \
    papermodel.cpp

HEADERS  += mainwindow.h \
    paper.h \
    papermodel.h

FORMS    += mainwindow.ui

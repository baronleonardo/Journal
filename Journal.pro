#-------------------------------------------------
#
# Project created by QtCreator 2017-03-25T19:43:16
#
#-------------------------------------------------

QT += core gui widgets

TARGET = Journal
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    papermodel.cpp \
    tool.cpp \
    pentool.cpp \
    selecttool.cpp \
    texttool.cpp \
    textbox.cpp \
    paperlist.cpp \
    paperview.cpp \
    papercontroller.cpp

HEADERS  += mainwindow.h \
    papermodel.h \
    tool.h \
    pentool.h \
    selecttool.h \
    texttool.h \
    textbox.h \
    paperlist.h \
    huge_dictionary.h \
    papercontroller.h \
    paperview.h

FORMS    += mainwindow.ui

DISTFILES += \
    README.md \
    uml.qmodel

RESOURCES += \
    assets.qrc

STATECHARTS +=

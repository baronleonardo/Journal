QT += core gui widgets

TARGET = qtmypaint
TEMPLATE = lib
CONFIG += staticlib

HEADERS += mpbrush.h \
           mphandler.h \
           mpsurface.h \
           mptile.h

SOURCES += mpbrush.cpp \
           mphandler.cpp \
           mpsurface.cpp \
           mptile.cpp

# --- json-c ---

INCLUDEPATH += ../json-c
DEPENDPATH += ../json-c

# --- libmypaint ---

INCLUDEPATH += ../libmypaint
DEPENDPATH += ../libmypaint

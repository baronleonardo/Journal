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
    selecttool.cpp \
    texttool.cpp \
    textbox.cpp \
    paperlist.cpp \
    paperview.cpp \
    papercontroller.cpp \
    mpbrushselector.cpp \
    mpbrush.cpp \
    mpbrushlib.cpp \
    mphandler.cpp \
    mpsurface.cpp \
    mptile.cpp \
    brushtool.cpp

HEADERS  += mainwindow.h \
    papermodel.h \
    tool.h \
    selecttool.h \
    texttool.h \
    textbox.h \
    paperlist.h \
    huge_dictionary.h \
    papercontroller.h \
    paperview.h \
    mpbrushselector.h \
    mpbrush.h \
    mpbrushlib.h \
    mphandler.h \
    mpsurface.h \
    mptile.h \
    brushtool.h

FORMS    += mainwindow.ui

DISTFILES += \
    README.md \
    uml.qmodel

RESOURCES += \
    assets.qrc

LIBS += -L../json-c -ljson-c
LIBS += -L../libmypaint -llibmypaint

# --- json-c ---
win32:CONFIG(release, debug|release): LIBS += -L../json-c/release/ -ljson-c
else:win32:CONFIG(debug, debug|release): LIBS += -L../json-c/debug/ -ljson-c
else:unix: LIBS += -L../json-c -ljson-c

INCLUDEPATH += ../json-c
DEPENDPATH += ../json-c

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += ../json-c/release/libjson-c.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += ../json-c/debug/libjson-c.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += ../json-c/release/json-c.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += ../json-c/debug/json-c.lib
else:unix: PRE_TARGETDEPS += ../json-c/libjson-c.a

# --- libmypaint ---
win32:CONFIG(release, debug|release): LIBS += -L../libmypaint/release/ -llibmypaint
else:win32:CONFIG(debug, debug|release): LIBS += -L../libmypaint/debug/ -llibmypaint
else:unix: LIBS += -L../libmypaint -llibmypaint

INCLUDEPATH += ../libmypaint
DEPENDPATH += ../libmypaint

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += ../libmypaint/release/liblibmypaint.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += ../libmypaint/debug/liblibmypaint.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += ../libmypaint/release/libmypaint.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += ../libmypaint/debug/libmypaint.lib
else:unix: PRE_TARGETDEPS += ../libmypaint/liblibmypaint.a

# --- qtmypaint ---
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qtmypaint/release/ -lqtmypaint
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qtmypaint/debug/ -lqtmypaint
else:unix: LIBS += -L$$OUT_PWD/../qtmypaint/ -lqtmypaint

INCLUDEPATH += ../libmypaint
INCLUDEPATH += ../qtmypaint
DEPENDPATH += ../qtmypaint

win32:CONFIG(release, debug|release): LIBS += -L../json-c/release -ljson-c
else:win32:CONFIG(debug, debug|release): LIBS += -L../json-c/debug -ljson-c
else:unix: LIBS += -L../json-c -ljson-c

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qtmypaint/release/libqtmypaint.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qtmypaint/debug/libqtmypaint.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qtmypaint/release/qtmypaint.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qtmypaint/debug/qtmypaint.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../qtmypaint/libqtmypaint.a

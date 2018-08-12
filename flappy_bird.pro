#-------------------------------------------------
#
# Project created by QtCreator 2018-08-04T22:44:26
#
#-------------------------------------------------

QT       += core gui widgets
QT += opengl
TARGET = Flappy-Bird
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    back_groud.cpp \
    myobject.cpp \
    sys.cpp \
    mylabel.cpp \
    bird.cpp \
    tools.cpp \
    pipe.cpp \
    mythread.cpp \
    score.cpp \
    scoreboard.cpp

HEADERS += \
        widget.h \
    back_groud.h \
    myobject.h \
    sys.h \
    mylabel.h \
    bird.h \
    tools.h \
    pipe.h \
    mythread.h \
    score.h \
    scoreboard.h

FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

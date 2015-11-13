#-------------------------------------------------
#
# Project created by QtCreator 2015-10-17T13:24:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    LPianoKey.cpp \
    LPianoKeyBoard.cpp \
    LPianoNote.cpp \
    LPianoPlain.cpp \
    LGraphicsPianoStripItem.cpp \
    LPianoRoll.cpp

HEADERS  += MainWindow.h \
    LPianoKey.h \
    LinneEditor.h \
    LPianoKeyBoard.h \
    LPianoNote.h \
    LPianoPlain.h \
    LGraphicsPianoStripItem.h \
    LPianoRoll.h

FORMS    += MainWindow.ui

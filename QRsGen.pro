#-------------------------------------------------
#
# Project created by QtCreator 2019-12-05T13:54:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32:RC_FILE = QRsGen.rc

TARGET = QRsGen
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        lib/qrencode.c \
        lib/split.c \
        lib/rsecc.c \
        lib/qrspec.c \
        lib/qrinput.c \
        lib/mqrspec.c \
        lib/mmask.c \
        lib/mask.c \
        lib/bitstream.c \
        argparser.cpp

DEFINES += "STATIC_IN_RELEASE=static"
DEFINES += "MAJOR_VERSION=0"
DEFINES += "MINOR_VERSION=0"
DEFINES += "MICRO_VERSION=0"
DEFINES += "VERSION="0""
DEFINES += "HAVE_STRDUP=1"


HEADERS  += mainwindow.h \
        lib/qrencode.h \
        lib/qrspec.h \
        lib/mqrspec.h \
        lib/bitstream.h \
        lib/qrinput.h \
        lib/split.h \
        lib/mask.h \
        argparser.h

FORMS    += mainwindow.ui

OTHER_FILES += \
            QRsGen.rc

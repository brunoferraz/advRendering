#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T16:37:03
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cookBook
TEMPLATE = app

CONFIG += c++11

LIBS += -lGLEW

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    shader.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    shader.h

FORMS    += mainwindow.ui

DISTFILES += \
    basic.vert \
    basic.frag

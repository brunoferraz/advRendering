#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T13:41:25
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = refactorTF
TEMPLATE = app

CONFIG += c++11

LIBS += -lGLEW

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    glslshader.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    glslshader.h

FORMS    += mainwindow.ui

DISTFILES += \
    basic.vert \
    basic.frag

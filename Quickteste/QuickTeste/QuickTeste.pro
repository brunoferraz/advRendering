QT += core opengl
QT -= gui



TARGET = QuickTeste
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += /usr/include/

LIBS += -lglut -lGL -lGLU -lGLEW

TEMPLATE = app

SOURCES += main.cpp \

DISTFILES += \
    basic.vert


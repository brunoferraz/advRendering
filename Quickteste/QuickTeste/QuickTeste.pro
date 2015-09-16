QT += core opengl
QT -= gui



TARGET = QuickTeste
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += /usr/include/

LIBS += -lglut -lGL -lGLU

TEMPLATE = app

SOURCES += main.cpp


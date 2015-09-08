#-------------------------------------------------
#
# Project created by QtCreator 2015-09-06T15:18:46
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newShaders
TEMPLATE = app

EIGEN_PATH  =  /usr/include/eigen3
TUCANO_PATH = $$PWD/../../tucano-master

BUILDDIR = $$PWD/../build/

LIBS += -lGLEW -lGLU

INCLUDEPATH +=  $$TUCANO_PATH/src $$TUCANO_PATH/effects $$EIGEN_PATH

OBJECTS_DIR =   $$BUILDDIR/obj
MOC_DIR =       $$BUILDDIR/moc
RCC_DIR =       $$BUILDDIR/rcc
UI_DIR =        $$BUILDDIR/ui
DESTDIR =       $$BUILDDIR/bin

QMAKE_CXXFLAGS += -DTUCANODEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp


HEADERS  += mainwindow.h \
        $$TUCANO_PATH/src/utils/qttrackballwidget.hpp \
        $$BUILDDIR/bin/effects/phongshader.hpp \
    glwidget.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    $$BUILDDIR/bin/effects/shaders/phongshader.vert \
    $$BUILDDIR/bin/effects/shaders/phongshader.frag \
    $$BUILDDIR/bin/effects/shaders/phongshader.geom \

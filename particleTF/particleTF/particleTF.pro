#-------------------------------------------------
#
# Project created by QtCreator 2015-09-11T15:17:06
#
#-------------------------------------------------

QT       += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = particleTF
TEMPLATE = app

EIGEN_PATH  =  /usr/include/eigen3
TUCANO_PATH = $$PWD/../../tucano-master

BUILDDIR = $$PWD/../build/

LIBS += -lGLEW -lGLU

INCLUDEPATH +=  $$TUCANO_PATH/src $$TUCANO_PATH/effects $$EIGEN_PATH $$BUILDDIR/effects particleStuff

#OBJECTS_DIR =   $$BUILDDIR/obj
#MOC_DIR =       $$BUILDDIR/moc
#RCC_DIR =       $$BUILDDIR/rcc
#UI_DIR =        $$BUILDDIR/ui
DESTDIR =       $$BUILDDIR

QMAKE_CXXFLAGS += -DTUCANODEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    particleStuff/pointcloud.cpp \
    particleStuff/particle.cpp \
    particleStuff/emitter.cpp

HEADERS  += mainwindow.h \
    $$BUILDDIR/effects/particleTF.hpp \
    $$BUILDDIR/effects/phongshader.hpp \
    $$TUCANO_PATH/src/utils/qttrackballwidget.hpp \
    glwidget.h \
    particleStuff/pointcloud.h \
    particleStuff/particle.h \
    particleStuff/emitter.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    $$BUILDDIR/effects/shaders/particleTF.vert \
    $$BUILDDIR/effects/shaders/particleTF.frag \
    $$BUILDDIR/effects/shaders/phongshader.vert \
    $$BUILDDIR/effects/shaders/phongshader.frag \

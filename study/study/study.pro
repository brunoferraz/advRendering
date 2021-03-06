#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T15:57:53
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = study
TEMPLATE = app

EIGEN_PATH  =  /usr/include/eigen3
TUCANO_PATH = $$PWD/../../../tucano
BUILDDIR = $$PWD/../build/bin

LIBS += -lGLEW -lGLU
INCLUDEPATH +=  $$TUCANO_PATH/src $$TUCANO_PATH/effects $$EIGEN_PATH $$BUILDDIR/effects

OBJECTS_DIR =   $$BUILDDIR/../obj
MOC_DIR =       $$BUILDDIR/../moc
RCC_DIR =       $$BUILDDIR/../rcc
UI_DIR =        $$BUILDDIR/../ui
DESTDIR =       $$BUILDDIR

QMAKE_CXXFLAGS += -DTUCANODEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    $$TUCANO_PATH/src/utils/qttrackballwidget.hpp \
    $$BUILDDIR/effects/phongshader.hpp \
    $$BUILDDIR/effects/tftest.hpp \
    $$BUILDDIR/effects/simpleTest.hpp \
    $$BUILDDIR/effects/simpleTF.hpp \
    $$BUILDDIR/effects/pingpong.hpp \

FORMS    += mainwindow.ui

DISTFILES += \
    ../build/bin/effects/shaders/pptf.vert \
    ../build/bin/effects/shaders/pptf.frag \
    ../build/bin/effects/shaders/tf.vert \
    ../build/bin/effects/shaders/tf.frag \
    ../build/bin/effects/shaders/tfrender.vert \
    ../build/bin/effects/shaders/tfrender.frag \
    ../build/bin/effects/shaders/pptfrender.vert \
    ../build/bin/effects/shaders/pptfrender.frag \
    ../build/bin/effects/shaders/simple.vert \
    ../build/bin/effects/shaders/simple.frag

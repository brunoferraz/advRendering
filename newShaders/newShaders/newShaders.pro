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
TUCANO_PATH = $$PWD/../../../tucano
SHADERS_PATH = $$PWD/../../build

BUILDDIR = $$PWD/../build/

LIBS += -lGLEW -lGLU

INCLUDEPATH +=  $$TUCANO_PATH/src $$TUCANO_PATH/effects $$EIGEN_PATH $$BUILDDIR/bin/effects $$SHADERS_PATH

#OBJECTS_DIR =   $$BUILDDIR/obj
#MOC_DIR =       $$BUILDDIR/moc
#RCC_DIR =       $$BUILDDIR/rcc
#UI_DIR =        $$BUILDDIR/ui
DESTDIR =       $$BUILDDIR/bin

QMAKE_CXXFLAGS += -DTUCANODEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    interface.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    interface.h \
        $$TUCANO_PATH/src/utils/qttrackballwidget.hpp \
        $$DESTDIR/effects/phongshader.hpp \
        $$DESTDIR/effects/phongcompleteshader.h \
        $$DESTDIR/effects/goochshader.h \
        $$DESTDIR/effects/ssfboshader.hpp \

FORMS    += mainwindow.ui

OTHER_FILES += \
    $$DESTDIR/effects/shaders/phongCompleteShader.vert \
    $$DESTDIR/effects/shaders/phongCompleteShader.frag \
    $$DESTDIR/effects/shaders/phongCompleteShader.geom \
    $$DESTDIR/effects/shaders/shownormals.vert \
    $$DESTDIR/effects/shaders/shownormals.frag \
    $$DESTDIR/effects/shaders/shownormals.geom \
    $$DESTDIR/effects/shaders/gooch.vert \
    $$DESTDIR/effects/shaders/gooch.frag \
    $$DESTDIR/effects/shaders/depthMap.vert \
    $$DESTDIR/effects/shaders/depthMap.frag \
    $$DESTDIR/effects/shaders/shadowMap.vert \
    $$DESTDIR/effects/shaders/shadowMap.frag \
    $$DESTDIR/effects/shaders/shadowMapClean.vert \
    $$DESTDIR/effects/shaders/shadowMapClean.frag \
    $$DESTDIR/effects/shaders/ssfboshader.vert \
    $$DESTDIR/effects/shaders/ssfboshader.frag \

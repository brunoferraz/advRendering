#-------------------------------------------------
#
# Project created by QtCreator 2015-07-28T17:12:21
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

EIGEN_PATH  =  /usr/include/eigen3

TUCANO_PATH = $$PWD/../tucano-master

SHADERS_PATH = $$PWD/../../build

LIBS += -lGLEW -lGLU

INCLUDEPATH +=  $$TUCANO_PATH/src $$TUCANO_PATH/effects $$EIGEN_PATH $$SHADERS_PATH

#DESTDIR = $$PWD/../build
DESTDIR = $$PWD/

TARGET   = Fbo
TEMPLATE = app

QMAKE_CXXFLAGS += -DTUCANODEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
        glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    $$DESTDIR/effects/ssfboshader.hpp \
    $$DESTDIR/effects/phongshader.hpp \
    ./../tucano-master/src/utils/qttrackballwidget.hpp

FORMS    += mainwindow.ui

OTHER_FILES +=  $$DESTDIR/effects/shaders/ssfboshader.vert \
                $$DESTDIR/effects/shaders/ssfboshader.frag \
                $$DESTDIR/effects/shaders/depthMap.vert \
                $$DESTDIR/effects/shaders/depthMap.frag \
                $$DESTDIR/effects/shaders/shadowMap.vert \
                $$DESTDIR/effects/shaders/shadowMap.frag \
                $$DESTDIR/effects/shaders/shadowMapClean.vert \
                $$DESTDIR/effects/shaders/shadowMapClean.frag \

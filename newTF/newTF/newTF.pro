#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T11:50:55
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newTF
TEMPLATE = app

EIGEN_PATH  =  /usr/include/eigen3
TUCANO_PATH = $$PWD/../../../tucano
BUILDDIR = $$PWD/../build/bin


LIBS += -lGLEW -lGLU
INCLUDEPATH +=  $$TUCANO_PATH/src $$TUCANO_PATH/effects $$EIGEN_PATH $$BUILDDIR/effects


OBJECTS_DIR =   $$BUILDDIR/obj
MOC_DIR =       $$BUILDDIR/moc
RCC_DIR =       $$BUILDDIR/rcc
UI_DIR =        $$BUILDDIR/ui
DESTDIR =       $$BUILDDIR

QMAKE_CXXFLAGS += -DTUCANODEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \


HEADERS  += mainwindow.h \
    glwidget.h \
    $$TUCANO_PATH/src/utils/qttrackballwidget.hpp \
    $$BUILDDIR/effects/phongshader.hpp \
    $$BUILDDIR/effects/tfTest.hpp \


FORMS    += mainwindow.ui

OTHER_FILES += \
    $$BUILDDIR/effects/shaders/tftestbasic.vert \
    $$BUILDDIR/effects/shaders/tftestbasic.frag \

#-------------------------------------------------
#
# Project created by QtCreator 2020-04-04T10:16:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XVMedio
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    xvideothread.cpp \
    xvideowidget.cpp

HEADERS += \
        mainwindow.h \
    xvideothread.h \
    xvideowidget.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += /opt/workspace/opencv-3.4.2/install/include \
              /opt/workspace/opencv-3.4.2/install/include/opencv \
              /opt/workspace/opencv-3.4.2/install/include/opencv2

LIBS += /opt/workspace/opencv-3.4.2/install/lib/libopencv_*

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

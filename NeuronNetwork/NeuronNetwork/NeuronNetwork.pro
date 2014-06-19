#-------------------------------------------------
#
# Project created by QtCreator 2014-06-19T22:58:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NeuronNetwork
TEMPLATE = app

#QGVCore library
unix {
    LIBS += -L$$OUT_PWD/../lib -lQGVCore
#    LIBS += -L/usr/lib64 -lQGVCore
    INCLUDEPATH += $$PWD/../include
    DEPENDPATH += $$PWD/../include
}

win32 {

}

SOURCES += main.cpp\
        mainwindow.cpp \
    graphicsview.cpp

HEADERS  += mainwindow.h \
    graphicsview.h

FORMS    += mainwindow.ui

RESOURCES += \
    res/res.qrc

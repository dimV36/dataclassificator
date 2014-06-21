#-------------------------------------------------
#
# Project created by QtCreator 2014-06-19T22:58:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NeuronNetwork
TEMPLATE = app

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
#QGVCore library
#unix {
    LIBS += -L$$OUT_PWD/../lib -lQGVCore
#    LIBS += -L/usr/lib64 -lQGVCore
#}
#win32 {
#    LIBS += 0L$$OUT_PWD/../lib -lQGVCore
#}

SOURCES += main.cpp\
        mainwindow.cpp \
    graphicsview.cpp \
    neuronnetworksettingsdialog.cpp \
    neuronexample.cpp \
    tablecolumnchooser.cpp

HEADERS  += mainwindow.h \
    graphicsview.h \
    neuronnetworksettingsdialog.h \
    neuronexample.h \
    tablecolumnchooser.h

FORMS    += mainwindow.ui \
    neuronnetworksettingsdialog.ui \
    tablecolumnchooser.ui

RESOURCES += \
    res/res.qrc

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/ -lQGVCore
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/ -lQGVCored

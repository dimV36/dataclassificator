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
LIBS += -L$$OUT_PWD/../lib -lQGVCore
INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

SOURCES += main.cpp\
        mainwindow.cpp \
    graphicsview.cpp \
    neuronnetworksettingsdialog.cpp \
    neuronexample.cpp \
    tablecolumnchooser.cpp \
    networkfunction.cpp \
    neurallink.cpp \
    neuralnetwork.cpp \
    neuron.cpp \
    neuronfactory.cpp \
    trainalgorithm.cpp

HEADERS  += mainwindow.h \
    graphicsview.h \
    neuronnetworksettingsdialog.h \
    neuronexample.h \
    tablecolumnchooser.h \
    networkfunction.h \
    neurallink.h \
    neuralnetwork.h \
    neuron.h \
    neuronfactory.h \
    trainalgorithm.h

FORMS    += mainwindow.ui \
    neuronnetworksettingsdialog.ui \
    tablecolumnchooser.ui

RESOURCES += \
    res/res.qrc

OTHER_FILES +=


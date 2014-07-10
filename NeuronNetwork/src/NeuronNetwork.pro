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
LIBS += -L$$OUT_PWD/../lib -lQGVCore -lNeuralNetwork
INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

SOURCES += main.cpp\
        mainwindow.cpp \
    graphicsview.cpp \
    neuronnetworksettingsdialog.cpp \
    tablecolumnchooser.cpp \
    neuralsample.cpp \
    node.cpp \
    classificatordialog.cpp

HEADERS  += mainwindow.h \
    graphicsview.h \
    neuronnetworksettingsdialog.h \
    tablecolumnchooser.h \
    neuralsample.h \
    node.h \
    classificatordialog.h

FORMS    += mainwindow.ui \
    neuronnetworksettingsdialog.ui \
    tablecolumnchooser.ui \
    classificatordialog.ui

RESOURCES += \
    res/res.qrc

OTHER_FILES +=


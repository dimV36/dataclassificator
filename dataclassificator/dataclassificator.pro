#-------------------------------------------------
#
# Project created by QtCreator 2014-05-25T23:07:39
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dataclassificator
TEMPLATE = app


SOURCES += main.cpp\
        classificator.cpp \
    qcustomplot.cpp \
    tablecolumnchooser.cpp \
    neuronexample.cpp \
    neuron.cpp \
    perceptron.cpp \
    teachprocess.cpp \
    addpointdialog.cpp \
    colorchooserdialog.cpp

HEADERS  += classificator.h \
    qcustomplot.h \
    tablecolumnchooser.h \
    neuronexample.h \
    neuron.h \
    perceptron.h \
    teachprocess.h \
    addpointdialog.h \
    colorchooserdialog.h

FORMS    += classificator.ui \
    tablecolumnchooser.ui \
    teachprocess.ui \
    addpointdialog.ui \
    colorchooserdialog.ui

RESOURCES += \
    res/resource.qrc

OTHER_FILES +=

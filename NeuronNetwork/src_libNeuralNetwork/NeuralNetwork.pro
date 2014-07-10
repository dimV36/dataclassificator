#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T13:43:34
#
#-------------------------------------------------

QT       += core

TARGET = NeuralNetwork
TEMPLATE = lib

DEFINES += NEURALNETWORK_LIBRARY

SOURCES += neuralnetwork.cpp \
    networkfunction.cpp \
    neurallink.cpp \
    neuron.cpp \
    neuronfactory.cpp \
    trainalgorithm.cpp

HEADERS += neuralnetwork.h\
        neuralnetwork_global.h \
    networkfunction.h \
    neurallink.h \
    neuron.h \
    neuronfactory.h \
    trainalgorithm.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

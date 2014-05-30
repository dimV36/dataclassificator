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
    tablecolumnchooser.cpp

HEADERS  += classificator.h \
    qcustomplot.h \
    tablecolumnchooser.h

FORMS    += classificator.ui \
    tablecolumnchooser.ui

RESOURCES += \
    res/resource.qrc

OTHER_FILES +=

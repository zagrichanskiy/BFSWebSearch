#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T22:54:10
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebSearch
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    tablemodel.cpp \
    bfsrunner.cpp \
    page.cpp \
    loader.cpp \
    worker.cpp \
    parser.cpp \
    newurlslist.cpp

HEADERS  += mainwindow.h \
    tablemodel.h \
    bfsrunner.h \
    page.h \
    loader.h \
    queue.h \
    worker.h \
    parser.h \
    newurlslist.h

FORMS    += mainwindow.ui

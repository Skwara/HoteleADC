#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T13:00:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HoteleADC
TEMPLATE = app

CONFIG += c++14

INCLUDEPATH = src

SOURCES += src/main.cpp\
           src/data/DatabaseHandler.cpp \
           src/logic/Client.cpp \
           src/logic/Reservation.cpp \
           src/ui/MainWindow.cpp \
           src/ui/NewReservationDialog.cpp

HEADERS  += src/data/DatabaseHandler.h \
            src/logic/Client.h \
            src/logic/Reservation.h \
            src/ui/MainWindow.h \
            src/ui/NewReservationDialog.h

FORMS    += src/ui/MainWindow.ui \
            src/ui/NewReservationDialog.ui

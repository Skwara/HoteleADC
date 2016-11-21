#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T13:00:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HoteleADC
TEMPLATE = app

INCLUDEPATH = src

SOURCES += src/main.cpp\
           src/ui/MainWindow.cpp \
           src/ui/NewReservationDialog.cpp \
           src/logic/Reservation.cpp

HEADERS  += src/ui/MainWindow.h \
            src/ui/NewReservationDialog.h \
            src/logic/Reservation.h

FORMS    += src/ui/MainWindow.ui \
            src/ui/NewReservationDialog.ui

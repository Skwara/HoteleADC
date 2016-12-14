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
           src/data/ScheduleModel.cpp \
           src/logic/Client.cpp \
           src/logic/Reservation.cpp \
           src/logic/Room.cpp \
           src/ui/MainWindow.cpp \
           src/ui/NewReservationDialog.cpp \
           src/ui/ScheduleDialog.cpp \
           src/ui/ScheduleView.cpp

HEADERS  += src/data/DatabaseHandler.h \
            src/data/ScheduleModel.h \
            src/logic/Client.h \
            src/logic/Reservation.h \
            src/logic/Room.h \
            src/ui/MainWindow.h \
            src/ui/NewReservationDialog.h \
            src/ui/ScheduleDialog.h \
            src/ui/ScheduleView.h

FORMS    += src/ui/MainWindow.ui \
            src/ui/NewReservationDialog.ui \
            src/ui/ScheduleDialog.ui

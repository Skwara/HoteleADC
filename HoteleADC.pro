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

SOURCES  += src/main.cpp \
            src/data/DatabaseHandler.cpp \
            src/data/ScheduleModel.cpp \
            src/data/RoomsModel.cpp \
            src/logic/Client.cpp \
            src/logic/Reservation.cpp \
            src/logic/Room.cpp \
            src/ui/MainWindow.cpp \
            src/ui/NewReservation/NewReservationDialog.cpp \
            src/ui/ScheduleDialog.cpp \
            src/ui/ScheduleTableView.cpp \
            src/ui/NewReservation/MainHandler.cpp \
            src/ui/NewReservation/ParticipantsHandler.cpp \
            src/ui/NewReservation/RoomsHandler.cpp \
    src/ui/NewReservation/DateHandler.cpp

HEADERS  += src/data/DatabaseHandler.h \
            src/data/ScheduleModel.h \
            src/data/RoomsModel.h \
            src/logic/Client.h \
            src/logic/Reservation.h \
            src/logic/Room.h \
            src/ui/MainWindow.h \
            src/ui/NewReservation/NewReservationDialog.h \
            src/ui/ScheduleDialog.h \
            src/ui/ScheduleTableView.h \
            src/ui/NewReservation/MainHandler.h \
            src/ui/NewReservation/ParticipantsHandler.h \
            src/ui/NewReservation/RoomsHandler.h \
    src/ui/NewReservation/DateHandler.h

FORMS    += src/ui/MainWindow.ui \
            src/ui/NewReservation/NewReservationDialog.ui \
            src/ui/ScheduleDialog.ui

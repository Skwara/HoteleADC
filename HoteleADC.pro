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
            src/data/ParticipantsModel.cpp \
            src/data/SpinBoxDelegate.cpp \
            src/logic/Client.cpp \
            src/logic/Reservation.cpp \
            src/logic/Room.cpp \
            src/logic/Price.cpp \
            src/ui/MainWindow.cpp \
            src/ui/ScheduleTableView.cpp \
            src/ui/NewReservation/NewReservationDialog.cpp \
            src/ui/NewReservation/MainHandler.cpp \
            src/ui/NewReservation/ParticipantsHandler.cpp \
            src/ui/NewReservation/RoomsHandler.cpp \
            src/ui/NewReservation/DateHandler.cpp \
            src/ui/NewReservation/AdditionalHandler.cpp \
            src/ui/NewReservation/SummaryHandler.cpp \
    src/data/SummaryModel.cpp

HEADERS  += src/data/DatabaseHandler.h \
            src/data/ScheduleModel.h \
            src/data/RoomsModel.h \
            src/data/ParticipantsModel.h \
            src/data/SpinBoxDelegate.h \
            src/logic/Client.h \
            src/logic/Reservation.h \
            src/logic/Room.h \
            src/logic/Price.h \
            src/ui/MainWindow.h \
            src/ui/ScheduleTableView.h \
            src/ui/NewReservation/NewReservationDialog.h \
            src/ui/NewReservation/MainHandler.h \
            src/ui/NewReservation/ParticipantsHandler.h \
            src/ui/NewReservation/RoomsHandler.h \
            src/ui/NewReservation/DateHandler.h \
            src/ui/NewReservation/AdditionalHandler.h \
            src/ui/NewReservation/SummaryHandler.h \
    src/data/SummaryModel.h

FORMS    += src/ui/MainWindow.ui \
            src/ui/NewReservation/NewReservationDialog.ui

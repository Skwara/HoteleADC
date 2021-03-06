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
            src/data/DataHandler.cpp \
            src/data/ScheduleModel.cpp \
            src/data/NewReservation/RoomsModel.cpp \
            src/data/NewReservation/ParticipantsModel.cpp \
            src/data/NewReservation/SummaryModel.cpp \
            src/data/NewReservation/BatchDateModel.cpp \
            src/data/NewReservation/ParticipantsSpinBoxDelegate.cpp \
            src/logic/Client.cpp \
            src/logic/Reservation.cpp \
            src/logic/Room.cpp \
            src/logic/Price.cpp \
            src/logic/Batch.cpp \
            src/ui/MainWindow.cpp \
            src/ui/ScheduleTableView.cpp \
            src/ui/NewReservation/NewReservationDialogInterface.cpp \
            src/ui/NewReservation/NewSingleDialog.cpp \
            src/ui/NewReservation/NewBatchDialog.cpp \
            src/ui/NewReservation/MainGroupBox.cpp \
            src/ui/NewReservation/RoomsGroupBox.cpp \
            src/ui/NewReservation/ParticipantsGroupBox.cpp \
            src/ui/NewReservation/AdditionalGroupBox.cpp \
            src/ui/NewReservation/SingleDateGroupBox.cpp \
            src/ui/NewReservation/BatchDateGroupBox.cpp \
            src/ui/NewReservation/SummaryGroupBox.cpp

HEADERS  += \
            src/data/DataHandler.h \
            src/data/ScheduleModel.h \
            src/data/NewReservation/RoomsModel.h \
            src/data/NewReservation/ParticipantsModel.h \
            src/data/NewReservation/SummaryModel.h \
            src/data/NewReservation/BatchDateModel.h \
            src/data/NewReservation/ParticipantsSpinBoxDelegate.h \
            src/logic/Client.h \
            src/logic/Reservation.h \
            src/logic/Room.h \
            src/logic/Price.h \
            src/logic/Batch.h \
            src/ui/MainWindow.h \
            src/ui/ScheduleTableView.h \
            src/ui/NewReservation/NewReservationDialogInterface.h \
            src/ui/NewReservation/NewSingleDialog.h \
            src/ui/NewReservation/NewBatchDialog.h \
            src/ui/NewReservation/MainGroupBox.h \
            src/ui/NewReservation/RoomsGroupBox.h \
            src/ui/NewReservation/ParticipantsGroupBox.h \
            src/ui/NewReservation/AdditionalGroupBox.h \
            src/ui/NewReservation/SingleDateGroupBox.h \
            src/ui/NewReservation/BatchDateGroupBox.h \
            src/ui/NewReservation/SummaryGroupBox.h

FORMS    += src/ui/MainWindow.ui \
            src/ui/NewReservation/NewSingleDialog.ui \
            src/ui/NewReservation/NewBatchDialog.ui \
            src/ui/NewReservation/MainGroupBox.ui \
            src/ui/NewReservation/RoomsGroupBox.ui \
            src/ui/NewReservation/ParticipantsGroupBox.ui \
            src/ui/NewReservation/AdditionalGroupBox.ui \
            src/ui/NewReservation/SingleDateGroupBox.ui \
            src/ui/NewReservation/BatchDateGroupBox.ui \
            src/ui/NewReservation/SummaryGroupBox.ui

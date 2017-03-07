#ifndef NEWRESERVATIONDIALOGINTERFACE_H
#define NEWRESERVATIONDIALOGINTERFACE_H

#include <QDialog>
#include <QItemSelection>
#include <QTableView>

#include "data/DatabaseHandler.h"
#include "logic/Reservation.h"
#include "MainGroupBox.h"
#include "RoomsGroupBox.h"
#include "ParticipantsGroupBox.h"
#include "AdditionalGroupBox.h"
#include "SummaryGroupBox.h"


class NewReservationDialogInterface : public QDialog
{
  Q_OBJECT

public:
  // TODO Change all constructors to take parent first without default 0 value
  explicit NewReservationDialogInterface(QWidget* parent = 0, ReservationPtr reservationToEdit = nullptr);
  virtual ~NewReservationDialogInterface() = 0;

public slots:
  virtual void onScheduleRoomSelectionChanged(QList<RoomPtr> selectedRooms);
  virtual void onScheduleDateSelectionChanged(QPair<QDate, QDate> selectedBeginEndDates) = 0;

signals:
  void reservationSaved();

protected:
  virtual void setupHandlers() = 0;

protected:
  DatabaseHandler* _dbHandler;
  ReservationPtr _reservation;
  ReservationPtr _reservationToEdit;

  MainGroupBox _mainGroupBox;
  RoomsGroupBox _roomsGroupBox;
  ParticipantsGroupBox _participantsGroupBox;
  AdditionalGroupBox _additionalGroupBox;
  SummaryGroupBox _summaryGroupBox;

private slots:
  void onSaveButtonClicked();

private:
  bool checkAvailability();
  bool setClient();
  bool saveReservation();
};

#endif // NEWRESERVATIONDIALOGINTERFACE_H

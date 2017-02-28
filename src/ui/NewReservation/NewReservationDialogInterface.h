#ifndef NEWRESERVATIONDIALOGINTERFACE_H
#define NEWRESERVATIONDIALOGINTERFACE_H

#include <QDialog>
#include <QItemSelection>

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
  explicit NewReservationDialogInterface(QWidget* parent = 0);
  virtual ~NewReservationDialogInterface() = 0;

public slots:
  virtual void scheduleSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

signals:
  void reservationSaved();

protected:
  virtual void setupHandlers() = 0;

protected:
  DatabaseHandler* _dbHandler;
  ReservationPtr _reservation;

  MainGroupBox _mainGroupBox;
  RoomsGroupBox _roomsGroupBox;
  ParticipantsGroupBox _participantsGroupBox;
  AdditionalGroupBox _additionalGroupBox;
  SummaryGroupBox _summaryGroupBox;

private slots:
  void onSaveButtonClicked();

private:
  bool checkAvailability();
  void setClient();
  void saveReservation();
};

#endif // NEWRESERVATIONDIALOGINTERFACE_H

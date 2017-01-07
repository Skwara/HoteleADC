#ifndef NEWRESERVATIONDIALOG_H
#define NEWRESERVATIONDIALOG_H

#include <QDialog>
#include <QItemSelection>

#include "logic/Reservation.h"
#include "data/DatabaseHandler.h"
#include "MainHandler.h"
#include "ParticipantsHandler.h"
#include "RoomsHandler.h"
#include "DateHandler.h"
#include "AdditionalHandler.h"
#include "SummaryHandler.h"


namespace Ui {
class NewReservationDialog;
}

class NewReservationDialog : public QDialog
{
  Q_OBJECT

public:
  explicit NewReservationDialog(QWidget* parent = 0);
  ~NewReservationDialog();

public slots:
  void scheduleSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
  Ui::NewReservationDialog* ui;

  Reservation _reservation;
  DatabaseHandler* _dbHandler;

  MainHandler _main;
  ParticipantsHandler _participants;
  RoomsHandler _rooms;
  DateHandler _date;
  AdditionalHandler _additional;
  SummaryHandler _summary;
};

#endif // NEWRESERVATIONDIALOG_H

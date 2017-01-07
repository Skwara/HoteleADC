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
  void prepareAdditional();
  void prepareSummary();

  void setSummaryDays(const int days);
  void setSummaryPrice(const int price);

private slots:
  void on_parkingCheckBox_toggled(bool checked);

private:
  Ui::NewReservationDialog* ui;

  Reservation _reservation;
  DatabaseHandler* _dbHandler;

  MainHandler _main;
  ParticipantsHandler _participants;
  RoomsHandler _rooms;
  DateHandler _date;
};

#endif // NEWRESERVATIONDIALOG_H

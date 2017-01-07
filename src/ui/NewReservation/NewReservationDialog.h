#ifndef NEWRESERVATIONDIALOG_H
#define NEWRESERVATIONDIALOG_H

#include <QDialog>
#include <QItemSelection>

#include "logic/Reservation.h"
#include "data/DatabaseHandler.h"
#include "MainHandler.h"
#include "ParticipantsHandler.h"


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
  void prepareRoom();
  void prepareDate();
  void prepareAdditional();
  void prepareSummary();

  void setSummaryDays(const int days);
  void setSummaryPrice(const int price);
  void setEndDateToBeginDate();

private slots:
  void on_beginCalendarWidget_clicked(const QDate &date);
  void on_endCalendarWidget_clicked(const QDate &date);

  void on_parkingCheckBox_toggled(bool checked);

  void onRoomListViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
  Ui::NewReservationDialog* ui;

  Reservation _reservation;
  DatabaseHandler* _dbHandler;

  MainHandler _main;
  ParticipantsHandler _participants;
};

#endif // NEWRESERVATIONDIALOG_H

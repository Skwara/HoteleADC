#ifndef NEWRESERVATIONDIALOG_H
#define NEWRESERVATIONDIALOG_H

#include <QDialog>

#include "data/DatabaseHandler.h"
#include "logic/Reservation.h"

namespace Ui {
class NewReservationDialog;
}

class NewReservationDialog : public QDialog
{
  Q_OBJECT

public:
  explicit NewReservationDialog(DatabaseHandler& dbHandler, QWidget* parent = 0);
  ~NewReservationDialog();

private:
  void prepareMain();
  void prepareDate();
  void prepareParticipants();
  void prepareSummary();

  void setSummaryDays(int days);
  void setEndDateToBeginDate();

private slots:
  void on_beginCalendarWidget_clicked(const QDate& date);
  void on_endCalendarWidget_clicked(const QDate& date);

  void on_addParticipantPushButton_clicked();

private:
  Ui::NewReservationDialog* ui;

  Reservation _reservation;
  DatabaseHandler& _dbHandler;
};

#endif // NEWRESERVATIONDIALOG_H

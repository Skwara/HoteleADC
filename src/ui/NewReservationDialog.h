#ifndef NEWRESERVATIONDIALOG_H
#define NEWRESERVATIONDIALOG_H

#include <QDialog>

#include "logic/Reservation.h"

namespace Ui {
class NewReservationDialog;
}

class NewReservationDialog : public QDialog
{
  Q_OBJECT

public:
  explicit NewReservationDialog(QWidget* parent = 0);
  ~NewReservationDialog();

private:
  void setSummaryDays(int days);
  void setEndDateToBeginDate();

private slots:
  void on_beginCalendarWidget_clicked(const QDate& date);
  void on_endCalendarWidget_clicked(const QDate& date);

private:
  Ui::NewReservationDialog* ui;

  Reservation reservation;

};

#endif // NEWRESERVATIONDIALOG_H

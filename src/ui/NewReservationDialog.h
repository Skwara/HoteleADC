#ifndef NEWRESERVATIONDIALOG_H
#define NEWRESERVATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSet>
#include <QString>
#include <QItemSelection>

#include "data/DatabaseHandler.h"
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

public slots:
  void scheduleSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
  void prepareMain();
  void prepareParticipants();
  void prepareRoom();
  void prepareDate();
  void prepareAdditional();
  void prepareSummary();

  void setSummaryDays(const int days);
  void setSummaryPrice(const int price);
  void setEndDateToBeginDate();

  void addCompleter(QLineEdit* lineEdit, QSet<QString> completions);
  void fillRemainingClientData(QString surname, QString name = "", QString street = "");

private slots:
  void on_beginCalendarWidget_clicked(const QDate& date);
  void on_endCalendarWidget_clicked(const QDate& date);

  void on_addParticipantPushButton_clicked();

  void on_surnameLineEdit_editingFinished();
  void on_nameLineEdit_editingFinished();
  void on_streetLineEdit_editingFinished();

  void on_parkingCheckBox_toggled(bool checked);

private:
  Ui::NewReservationDialog* ui;

  Reservation _reservation;
  DatabaseHandler* _dbHandler;
};

#endif // NEWRESERVATIONDIALOG_H

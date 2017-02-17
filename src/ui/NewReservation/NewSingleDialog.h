#ifndef NEWSINGLEDIALOG_H
#define NEWSINGLEDIALOG_H

#include <QDialog>
#include <QItemSelection>
#include <QSet>
#include <QItemSelectionModel>

#include "logic/Reservation.h"
#include "data/DatabaseHandler.h"
#include "MainHandler.h"
#include "ParticipantsHandler.h"
#include "RoomsHandler.h"
#include "AdditionalHandler.h"
#include "DateHandler.h"
#include "SummaryHandler.h"


namespace Ui {
class NewSingleDialog;
}

class NewSingleDialog : public QDialog
{
  Q_OBJECT

public:
  explicit NewSingleDialog(QWidget* parent = 0);
  ~NewSingleDialog();

public slots:
  void scheduleSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

signals:
  void reservationSaved();

private slots:
  void onSaveButtonClicked();

private:
  void setupHandlers();

  QSet<int> getSelectedRows(QSet<QModelIndex> allSelected);
  QSet<int> getSelectedCols(QSet<QModelIndex> allSelected);

private:
  Ui::NewSingleDialog* ui;

  ReservationPtr _reservation;
  DatabaseHandler* _dbHandler;

  MainHandler _main;
  RoomsHandler _rooms;
  ParticipantsHandler _participants;
  AdditionalHandler _additional;
  DateHandler _date;
  SummaryHandler _summary;
};

#endif // NewSingleDialog_H

#ifndef NEWSINGLEDIALOG_H
#define NEWSINGLEDIALOG_H

#include <QDialog>
#include <QItemSelection>
#include <QSet>
#include <QItemSelectionModel>

#include "logic/Reservation.h"
#include "data/DatabaseHandler.h"
#include "SummaryHandler.h"

#include "MainGroupBox.h"
#include "RoomsGroupBox.h"
#include "ParticipantsGroupBox.h"
#include "AdditionalGroupBox.h"
#include "SingleDateGroupBox.h"


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

  SummaryHandler _summary;

  MainGroupBox _mainGroupBox;
  RoomsGroupBox _roomsGroupBox;
  ParticipantsGroupBox _participantsGroupBox;
  AdditionalGroupBox _additionalGroupBox;
  SingleDateGroupBox _singleDateGroupBox;
};

#endif // NewSingleDialog_H

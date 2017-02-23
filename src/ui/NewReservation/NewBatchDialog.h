#ifndef NEWBATCHDIALOG_H
#define NEWBATCHDIALOG_H

#include <QDialog>
#include <QItemSelection>
#include <QSet>
#include <QItemSelectionModel>

#include "logic/Reservation.h"
#include "data/DatabaseHandler.h"
#include "MainGroupBox.h"
#include "RoomsGroupBox.h"
#include "ParticipantsGroupBox.h"
#include "AdditionalGroupBox.h"
#include "BatchDateGroupBox.h"
#include "SummaryGroupBox.h"


namespace Ui {
class NewBatchDialog;
}

class NewBatchDialog : public QDialog // TODO BATCH Extract interface
{
  Q_OBJECT

public:
  explicit NewBatchDialog(QWidget* parent = 0);
  ~NewBatchDialog();

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
  Ui::NewBatchDialog* ui;

  ReservationPtr _reservation;
  DatabaseHandler* _dbHandler;

  MainGroupBox _mainGroupBox;
  RoomsGroupBox _roomsGroupBox;
  ParticipantsGroupBox _participantsGroupBox;
  AdditionalGroupBox _additionalGroupBox;
  BatchDateGroupBox _batchDateGroupBox;
  SummaryGroupBox _summaryGroupBox;
};

#endif // NEWBATCHDIALOG_H

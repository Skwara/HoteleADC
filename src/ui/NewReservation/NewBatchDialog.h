#ifndef NEWBATCHDIALOG_H
#define NEWBATCHDIALOG_H

#include "NewReservationDialogInterface.h"
#include "BatchDateGroupBox.h"


namespace Ui {
class NewBatchDialog;
}

class NewBatchDialog : public NewReservationDialogInterface
{
  Q_OBJECT

public:
  explicit NewBatchDialog(QWidget* parent = 0, ReservationPtr reservationToEdit = nullptr);
  virtual ~NewBatchDialog();

private:
  void setupHandlers();

private:
  Ui::NewBatchDialog* ui;
  BatchDateGroupBox _batchDateGroupBox;
};

#endif // NEWBATCHDIALOG_H

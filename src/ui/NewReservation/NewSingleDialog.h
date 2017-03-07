#ifndef NEWSINGLEDIALOG_H
#define NEWSINGLEDIALOG_H

#include <QSet>

#include "NewReservationDialogInterface.h"
#include "SingleDateGroupBox.h"


namespace Ui {
class NewSingleDialog;
}

class NewSingleDialog : public NewReservationDialogInterface
{
  Q_OBJECT

public:
  explicit NewSingleDialog(QWidget* parent = 0, ReservationPtr reservationToEdit = nullptr);
  virtual ~NewSingleDialog();

public slots:
  virtual void onScheduleDateSelectionChanged(QPair<QDate, QDate> selectedBeginEndDates);

private:
  virtual void setupHandlers();

private:
  Ui::NewSingleDialog* ui;
  SingleDateGroupBox _singleDateGroupBox;
};

#endif // NewSingleDialog_H

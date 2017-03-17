#ifndef BATCHDATEGROUPBOX_H
#define BATCHDATEGROUPBOX_H

#include <QGroupBox>

#include "data/DataHandler.h"
#include "data/NewReservation/BatchDateModel.h"


namespace Ui {
class BatchDateGroupBox;
}

class BatchDateGroupBox : public QGroupBox
{
  Q_OBJECT

public:
  explicit BatchDateGroupBox(ReservationPtr reservation, QWidget* parent = 0);
  ~BatchDateGroupBox();

public slots:
  void update();
  void update(QPair<QDate, QDate> selectedBeginEndDates);

private:
  void setup();
  void selectBatch(BatchPtr batch);

private slots:
  void onDateTableViewClicked(const QModelIndex& index);

private:
  Ui::BatchDateGroupBox* ui;
  DataHandler* _dataHandler;

  ReservationPtr _reservation;
  BatchDateModel _batchDateModel;
};

#endif // BATCHDATEGROUPBOX_H

#ifndef BATCHDATEGROUPBOX_H
#define BATCHDATEGROUPBOX_H

#include <QGroupBox>

#include "data/DatabaseHandler.h"
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
  void update(QSet<int> selectedCols);
  void update();

private:
  void setup();

private slots:
  void onDateTableViewClicked(const QModelIndex& index);

private:
  Ui::BatchDateGroupBox* ui;
  DatabaseHandler* _dbHandler;

  ReservationPtr _reservation;
  BatchDateModel _batchDateModel;
};

#endif // BATCHDATEGROUPBOX_H

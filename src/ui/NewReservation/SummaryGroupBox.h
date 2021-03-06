#ifndef SUMMARYGROUPBOX_H
#define SUMMARYGROUPBOX_H

#include <QGroupBox>

#include "data/DataHandler.h"
#include "data/NewReservation/SummaryModel.h"


namespace Ui {
class SummaryGroupBox;
}

class SummaryGroupBox : public QGroupBox
{
  Q_OBJECT

public:
  explicit SummaryGroupBox(ReservationPtr reservation, QWidget* parent = 0);
  ~SummaryGroupBox();

signals:
  void saveButtonClicked();

public slots:
  void update();

private:
  void setup();

private:
  Ui::SummaryGroupBox* ui;
  DataHandler* _dataHandler;

  ReservationPtr _reservation;
  SummaryModel _summaryModel;
};

#endif // SUMMARYGROUPBOX_H

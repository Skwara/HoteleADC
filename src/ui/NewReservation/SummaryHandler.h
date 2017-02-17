#ifndef SUMMARYHANDLER_H
#define SUMMARYHANDLER_H

#include <QObject>

#include "data/DatabaseHandler.h"
#include "data/NewReservation/SummaryModel.h"


namespace Ui {
class NewSingleDialog;
}

class SummaryHandler : public QObject
{
  Q_OBJECT

public:
  explicit SummaryHandler(Ui::NewSingleDialog* ui, ReservationPtr reservation, QObject* parent = 0);

  void setup();

public slots:
  void update();

private:
  Ui::NewSingleDialog* ui;
  DatabaseHandler* _dbHandler;

  ReservationPtr _reservation;
  SummaryModel _summaryModel;
};

#endif // SUMMARYHANDLER_H

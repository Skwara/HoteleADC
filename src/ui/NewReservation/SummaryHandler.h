#ifndef SUMMARYHANDLER_H
#define SUMMARYHANDLER_H

#include <QObject>

#include "data/DatabaseHandler.h"
#include "data/SummaryModel.h"


namespace Ui {
class NewReservationDialog;
}

class SummaryHandler : public QObject
{
  Q_OBJECT

public:
  explicit SummaryHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent = 0);

  void setup();

public slots:
  void update();

private:
  Ui::NewReservationDialog* ui;
  DatabaseHandler* _dbHandler;

  Reservation& _reservation;
  SummaryModel _summaryModel;
};

#endif // SUMMARYHANDLER_H

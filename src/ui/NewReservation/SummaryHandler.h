#ifndef SUMMARYHANDLER_H
#define SUMMARYHANDLER_H

#include <QObject>

#include "data/DatabaseHandler.h"


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
  void prepare();

private:
  void setSummaryDays(const int days);
  void setSummaryPrice(const int price);

private:
  Ui::NewReservationDialog* ui;
  DatabaseHandler* _dbHandler;

  Reservation& _reservation;
};

#endif // SUMMARYHANDLER_H

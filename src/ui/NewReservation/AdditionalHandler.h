#ifndef ADDITIONALHANDLER_H
#define ADDITIONALHANDLER_H

#include <QObject>

#include "data/DatabaseHandler.h"


namespace Ui {
class NewReservationDialog;
}

class AdditionalHandler : public QObject
{
  Q_OBJECT

public:
  explicit AdditionalHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent = 0);

  void setup();

public slots:
  void prepare();

signals:
  void additionalChanged();

private slots:
  void onParkingCheckBoxToggled(bool checked);

private:
  Ui::NewReservationDialog* ui;
  DatabaseHandler* _dbHandler;

  Reservation& _reservation;
};

#endif // ADDITIONALHANDLER_H

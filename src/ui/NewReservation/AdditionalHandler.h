#ifndef ADDITIONALHANDLER_H
#define ADDITIONALHANDLER_H

#include <QObject>

#include "data/DatabaseHandler.h"


namespace Ui {
class NewSingleDialog;
}

class AdditionalHandler : public QObject
{
  Q_OBJECT

public:
  explicit AdditionalHandler(Ui::NewSingleDialog* ui, ReservationPtr reservation, QObject* parent = 0);

  void setup();

public slots:
  void update();

private slots:
  void onParkingCheckBoxToggled(bool checked);
  void onEmptyPlaceCheckBoxToggled(bool checked);

private:
  Ui::NewSingleDialog* ui;
  DatabaseHandler* _dbHandler;

  ReservationPtr _reservation;
};

#endif // ADDITIONALHANDLER_H

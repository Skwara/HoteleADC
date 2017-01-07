#ifndef ROOMSHANDLER_H
#define ROOMSHANDLER_H

#include <QObject>
#include <QItemSelection>

#include "data/DatabaseHandler.h"


namespace Ui {
class NewReservationDialog;
}

class RoomsHandler : public QObject
{
  Q_OBJECT

public:
  explicit RoomsHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent = 0);

  void setup();
  void prepare();

private slots:
  void onRoomListViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
  Ui::NewReservationDialog* ui;
  DatabaseHandler* _dbHandler;

  Reservation& _reservation;
};

#endif // ROOMSHANDLER_H

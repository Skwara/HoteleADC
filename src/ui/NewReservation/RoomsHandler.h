#ifndef ROOMSHANDLER_H
#define ROOMSHANDLER_H

#include <QObject>
#include <QSet>
#include <QItemSelection>

#include "data/DatabaseHandler.h"
#include "src/data/NewReservation/RoomsModel.h"


namespace Ui {
class NewReservationDialog;
}

class RoomsHandler : public QObject
{
  Q_OBJECT

public:
  explicit RoomsHandler(Ui::NewReservationDialog* ui, ReservationPtr reservation, QObject* parent = 0);

  void setup();

public slots:
  void update(QSet<int> selectedRows);

private slots:
  void onRoomListViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
  Ui::NewReservationDialog* ui;
  DatabaseHandler* _dbHandler;

  ReservationPtr _reservation;
  RoomsModel _roomsModel;
};

#endif // ROOMSHANDLER_H

#ifndef ROOMSGROUPBOX_H
#define ROOMSGROUPBOX_H

#include <QGroupBox>
#include <QSet>
#include <QItemSelection>

#include "data/DatabaseHandler.h"
#include "src/data/NewReservation/RoomsModel.h"


namespace Ui {
class RoomsGroupBox;
}

class RoomsGroupBox : public QGroupBox
{
  Q_OBJECT

public:
  explicit RoomsGroupBox(ReservationPtr reservation, QWidget* parent = 0);
  ~RoomsGroupBox();

public slots:
  void update(QSet<int> selectedRows);

private:
  void setup();

private slots:
  void onRoomListViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
  Ui::RoomsGroupBox* ui;
  DatabaseHandler* _dbHandler;

  ReservationPtr _reservation;
  RoomsModel _roomsModel;
};

#endif // ROOMSGROUPBOX_H

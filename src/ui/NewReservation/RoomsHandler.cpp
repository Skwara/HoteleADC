#include "RoomsHandler.h"
#include "ui_NewReservationDialog.h"

#include "src/data/RoomsModel.h"


RoomsHandler::RoomsHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
{
}

void RoomsHandler::setup()
{
  ui->roomListView->setModel(RoomsModel::instance());
  ui->roomListView->setSelectionMode(QAbstractItemView::ExtendedSelection);

  connect(ui->roomListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onRoomListViewSelectionChanged(QItemSelection,QItemSelection)));
}

void RoomsHandler::prepare()
{
}

void RoomsHandler::onRoomListViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
  foreach (QModelIndex index, selected.indexes())
  {
    RoomPtr room = _dbHandler->room(ui->roomListView->model()->data(index).toInt());
    _reservation.addRoom(room);
  }

  foreach (QModelIndex index, deselected.indexes())
  {
    RoomPtr room = _dbHandler->room(ui->roomListView->model()->data(index).toInt());
    _reservation.removeRoom(room);
  }
}

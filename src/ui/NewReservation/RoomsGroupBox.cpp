#include "RoomsGroupBox.h"
#include "ui_RoomsGroupBox.h"

RoomsGroupBox::RoomsGroupBox(ReservationPtr reservation, QWidget* parent)
  : QGroupBox(parent)
  , ui(new Ui::RoomsGroupBox)
  , _dataHandler(DataHandler::instance())
  , _reservation(reservation)
  , _roomsModel()
{
  ui->setupUi(this);
  setup();
}

RoomsGroupBox::~RoomsGroupBox()
{
  delete ui;
}

void RoomsGroupBox::update()
{
  this->blockSignals(true);
  selectRooms(_reservation->rooms());
  this->blockSignals(false);
}

void RoomsGroupBox::update(QList<RoomPtr> selectedRooms)
{
  selectRooms(selectedRooms);
}

void RoomsGroupBox::setup()
{
  ui->roomListView->setModel(&_roomsModel);
  ui->roomListView->setSelectionMode(QAbstractItemView::ExtendedSelection);

  connect(ui->roomListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onRoomListViewSelectionChanged(QItemSelection,QItemSelection)));

  update();
}

void RoomsGroupBox::selectRooms(QList<RoomPtr> rooms)
{
  foreach (QModelIndex index, ui->roomListView->selectionModel()->selectedIndexes())
    if (!rooms.contains(_roomsModel.sourceRoom(index.row())))
      ui->roomListView->selectionModel()->select(index, QItemSelectionModel::Deselect);

  foreach (RoomPtr room, rooms)
    ui->roomListView->selectionModel()->select(_roomsModel.index(_roomsModel.roomRow(room), 0), QItemSelectionModel::Select);
}

void RoomsGroupBox::onRoomListViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
  foreach (QModelIndex index, selected.indexes())
  {
    RoomPtr room = _roomsModel.sourceRoom(index.row());
    _reservation->addRoom(room);
  }

  foreach (QModelIndex index, deselected.indexes())
  {
    RoomPtr room = _roomsModel.sourceRoom(index.row());
    _reservation->removeRoom(room);
  }
}

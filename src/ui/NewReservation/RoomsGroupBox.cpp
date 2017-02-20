#include "RoomsGroupBox.h"
#include "ui_RoomsGroupBox.h"

RoomsGroupBox::RoomsGroupBox(ReservationPtr reservation, QWidget* parent)
  : QGroupBox(parent)
  , ui(new Ui::RoomsGroupBox)
  , _dbHandler(DatabaseHandler::instance())
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

void RoomsGroupBox::update(QSet<int> selectedRows)
{
  QAbstractItemModel* model = ui->roomListView->model();
  for (int i = 0; i < ui->roomListView->model()->rowCount(); ++i)
  {
    if (selectedRows.contains(i) && !ui->roomListView->selectionModel()->isRowSelected(i, QModelIndex()))
    {
      ui->roomListView->selectionModel()->select(model->index(i, 0), QItemSelectionModel::Select);
    }
    else if (!selectedRows.contains(i) && ui->roomListView->selectionModel()->isRowSelected(i, QModelIndex()))
    {
      ui->roomListView->selectionModel()->select(model->index(i, 0), QItemSelectionModel::Deselect);
    }
  }
}

void RoomsGroupBox::setup()
{
  ui->roomListView->setModel(&_roomsModel);
  ui->roomListView->setSelectionMode(QAbstractItemView::ExtendedSelection);

  connect(ui->roomListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onRoomListViewSelectionChanged(QItemSelection,QItemSelection)));
}

void RoomsGroupBox::onRoomListViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
  foreach (QModelIndex index, selected.indexes())
  {
    RoomPtr room = _dbHandler->room(ui->roomListView->model()->data(index).toInt());
    _reservation->addRoom(room);
  }

  foreach (QModelIndex index, deselected.indexes())
  {
    RoomPtr room = _dbHandler->room(ui->roomListView->model()->data(index).toInt());
    _reservation->removeRoom(room);
  }
}

#include "NewReservationDialog.h"
#include "ui_NewReservationDialog.h"


NewReservationDialog::NewReservationDialog(QWidget* parent)
  : QDialog(parent)
  , ui(new Ui::NewReservationDialog)
  , _reservation()
  , _dbHandler(DatabaseHandler::instance())
  , _main(ui, this)
  , _participants(ui, this)
  , _rooms(ui, _reservation, this)
  , _date(ui, _reservation, this)
  , _additional(ui, _reservation, this)
  , _summary(ui, _reservation, this)
{
  ui->setupUi(this);
  _main.setup();
  _participants.setup();
  _rooms.setup();
  _date.setup();
  _additional.setup();
  _summary.setup();

  connect(&_rooms, SIGNAL(roomsChanged()), &_summary, SLOT(prepare()));
  connect(&_date, SIGNAL(dateChanged()), &_additional, SLOT(prepare()));
  connect(&_date, SIGNAL(dateChanged()), &_summary, SLOT(prepare()));
  connect(&_additional, SIGNAL(additionalChanged()), &_summary, SLOT(prepare()));

  setAttribute(Qt::WA_DeleteOnClose, true);
}

NewReservationDialog::~NewReservationDialog()
{
  delete ui;
}

void NewReservationDialog::scheduleSelectionChanged(const QItemSelection& /*selected*/, const QItemSelection& /*deselected*/)
{
  QItemSelectionModel* selectionModel = qobject_cast<QItemSelectionModel*>(sender());
  QSet<QModelIndex> allSelected = selectionModel->selectedIndexes().toSet();

  QSet<int> selectedRows = getSelectedRows(allSelected);
  QSet<int> selectedCols = getSelectedCols(allSelected);

  _rooms.prepare(selectedRows);
  _date.prepare(selectedCols);
}

QSet<int> NewReservationDialog::getSelectedRows(QSet<QModelIndex> allSelected)
{
  QSet<int> selectedRows;
  foreach (QModelIndex index, allSelected)
  {
    selectedRows += index.row();
  }

  return selectedRows;
}

QSet<int> NewReservationDialog::getSelectedCols(QSet<QModelIndex> allSelected)
{
  QSet<int> selectedCols;
  foreach (QModelIndex index, allSelected)
  {
    selectedCols += index.column();
  }

  return selectedCols;
}

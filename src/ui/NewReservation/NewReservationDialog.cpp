#include "NewReservationDialog.h"
#include "ui_NewReservationDialog.h"


NewReservationDialog::NewReservationDialog(QWidget* parent)
  : QDialog(parent)
  , ui(new Ui::NewReservationDialog)
  , _reservation()
  , _dbHandler(DatabaseHandler::instance())
  , _main(ui, this)
  , _rooms(ui, _reservation, this)
  , _participants(ui, _reservation, this)
  , _additional(ui, _reservation, this)
  , _date(ui, _reservation, this)
  , _summary(ui, _reservation, this)
{
  ui->setupUi(this);
  setupHandlers();

  this->resize(this->minimumWidth(), this->minimumHeight());
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

  _rooms.update(selectedRows);
  _date.update(selectedCols);
}

void NewReservationDialog::setupHandlers()
{
  _main.setup();
  _rooms.setup();
  _participants.setup();
  _additional.setup();
  _date.setup();
  _summary.setup();
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

#include "NewSingleDialog.h"
#include "ui_NewSingleDialog.h"


NewSingleDialog::NewSingleDialog(QWidget* parent)
  : NewReservationDialogInterface(parent)
  , ui(new Ui::NewSingleDialog)
  , _singleDateGroupBox(_reservation, this)
{
  ui->setupUi(this);
  setupHandlers();
}

NewSingleDialog::~NewSingleDialog()
{
  delete ui;
}

void NewSingleDialog::scheduleSelectionChanged(const QItemSelection& /*selected*/, const QItemSelection& /*deselected*/)
{
  QItemSelectionModel* selectionModel = qobject_cast<QItemSelectionModel*>(sender());
  QSet<QModelIndex> allSelected = selectionModel->selectedIndexes().toSet();

  QSet<int> selectedRows = getSelectedRows(allSelected);
  QSet<int> selectedCols = getSelectedCols(allSelected);

  _roomsGroupBox.update(selectedRows);
  _singleDateGroupBox.update(selectedCols);
}

void NewSingleDialog::setupHandlers()
{
  ui->horizontalLayout_1->insertWidget(0, &_mainGroupBox);
  ui->horizontalLayout_1->insertWidget(1, &_roomsGroupBox);
  ui->horizontalLayout_1->insertWidget(2, &_participantsGroupBox);
  ui->horizontalLayout_1->insertWidget(3, &_additionalGroupBox);
  ui->horizontalLayout_2->insertWidget(0, &_singleDateGroupBox);
  ui->horizontalLayout_2->insertWidget(1, &_summaryGroupBox);
}

QSet<int> NewSingleDialog::getSelectedRows(QSet<QModelIndex> allSelected)
{
  QSet<int> selectedRows;
  foreach (QModelIndex index, allSelected)
  {
    selectedRows += index.row();
  }

  return selectedRows;
}

QSet<int> NewSingleDialog::getSelectedCols(QSet<QModelIndex> allSelected)
{
  QSet<int> selectedCols;
  foreach (QModelIndex index, allSelected)
  {
    selectedCols += index.column();
  }

  return selectedCols;
}

#include "NewSingleDialog.h"
#include "ui_NewSingleDialog.h"

#include <QMessageBox>


NewSingleDialog::NewSingleDialog(QWidget* parent)
  : QDialog(parent)
  , ui(new Ui::NewSingleDialog)
  , _reservation(std::make_shared<Reservation>())
  , _dbHandler(DatabaseHandler::instance())
  , _mainGroupBox(this)
  , _roomsGroupBox(_reservation, this)
  , _participantsGroupBox(_reservation, this)
  , _additionalGroupBox(_reservation, this)
  , _singleDateGroupBox(_reservation, this)
  , _summaryGroupBox(_reservation, this)
{
  ui->setupUi(this);
  setupHandlers();

  connect(&_summaryGroupBox, SIGNAL(saveButtonClicked()), this, SLOT(onSaveButtonClicked()));

  this->resize(this->minimumWidth(), this->minimumHeight());
  setAttribute(Qt::WA_DeleteOnClose, true);
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

void NewSingleDialog::onSaveButtonClicked()
{
  // TODO Check if room and date is available
  QList<ClientPtr> clients = _dbHandler->clients(_mainGroupBox.surname(), _mainGroupBox.name(), _mainGroupBox.street());
  if (clients.size() == 0)
  {
    _reservation->setClient(_mainGroupBox.createClient());
  }
  else if (clients.size() == 1)
  {
    _reservation->setClient(clients.first());
  }
  else
  {
    // TODO handle selection of multiple clients
  }

  if (!_dbHandler->saveReservation(_reservation))
  {
    int ret = QMessageBox::critical(this, "Error", "Reservation cannot be saved", QMessageBox::Abort | QMessageBox::Retry);
    while (ret == QMessageBox::Retry)
    {
      if (!_dbHandler->saveReservation(_reservation))
      {
        ret = QMessageBox::critical(this, "Error", "Reservation cannot be saved", QMessageBox::Abort | QMessageBox::Retry);
        continue;
      }
      emit reservationSaved();
    }
    return;
  }

  emit reservationSaved();
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

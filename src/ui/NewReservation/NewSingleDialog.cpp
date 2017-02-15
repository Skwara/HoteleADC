#include "NewSingleDialog.h"
#include "ui_NewSingleDialog.h"

#include <QMessageBox>


NewSingleDialog::NewSingleDialog(QWidget* parent)
  : QDialog(parent)
  , ui(new Ui::NewSingleDialog)
  , _reservation(std::make_shared<Reservation>())
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

  connect(ui->summarySaveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));

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

  _rooms.update(selectedRows);
  _date.update(selectedCols);
}

void NewSingleDialog::onSaveButtonClicked()
{
  QList<ClientPtr> clients = _dbHandler->clients(ui->surnameLineEdit->text(), ui->nameLineEdit->text(), ui->streetLineEdit->text());
  if (clients.size() == 0)
  {
    _reservation->setClient(createClient());
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
  _main.setup();
  _rooms.setup();
  _participants.setup();
  _additional.setup();
  _date.setup();
  _summary.setup();
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

ClientPtr NewSingleDialog::createClient() const
{
  return std::make_shared<Client>(ui->surnameLineEdit->text(),
                                  ui->nameLineEdit->text(),
                                  Address(ui->streetLineEdit->text(),
                                          ui->numberLineEdit->text(),
                                          ui->postalCodeLineEdit->text(),
                                          ui->cityLineEdit->text(),
                                          ui->countryLineEdit->text()),
                                  ui->phoneLineEdit->text(),
                                  ui->emailLineEdit->text());
}

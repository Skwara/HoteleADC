#include "NewReservationDialogInterface.h"

#include <QMessageBox>


NewReservationDialogInterface::NewReservationDialogInterface(QWidget* parent)
  : QDialog(parent)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(std::make_shared<Reservation>())
  , _mainGroupBox(this)
  , _roomsGroupBox(_reservation, this)
  , _participantsGroupBox(_reservation, this)
  , _additionalGroupBox(_reservation, this)
  , _summaryGroupBox(_reservation, this)
{
  connect(&_summaryGroupBox, SIGNAL(saveButtonClicked()), this, SLOT(onSaveButtonClicked()));

  this->resize(this->minimumWidth(), this->minimumHeight());
  setAttribute(Qt::WA_DeleteOnClose, true);
}

NewReservationDialogInterface::~NewReservationDialogInterface()
{
}

void NewReservationDialogInterface::scheduleSelectionChanged(const QItemSelection& /*selected*/, const QItemSelection& /*deselected*/)
{
}

void NewReservationDialogInterface::onSaveButtonClicked()
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

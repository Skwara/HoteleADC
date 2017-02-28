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
  if (!checkAvailability())
    return;
  setClient();
  saveReservation();
}

bool NewReservationDialogInterface::checkAvailability()
{
  if (!_dbHandler->isReservationAvailable(_reservation))
  {
    QMessageBox::critical(this, "Błąd", "Pokoje nie są dostępne w wybranym terminie", QMessageBox::Ok);
    return false;
  }
  return true;
}

void NewReservationDialogInterface::setClient()
{
  QList<ClientPtr> clients = _dbHandler->clients(_mainGroupBox.surname(), _mainGroupBox.name(), _mainGroupBox.street());
  if (clients.size() == 0)
    _reservation->setClient(_mainGroupBox.createClient());
  else if (clients.size() == 1)
    _reservation->setClient(clients.first());
  else
    return; // TODO handle selection of multiple clients
}

void NewReservationDialogInterface::saveReservation()
{
  bool saved = false;
  while (!saved)
  {
    if (_dbHandler->saveReservation(_reservation))
      saved = true;
    else if (QMessageBox::critical(this, "Błąd", "Nie można zapisać rezerwacji", QMessageBox::Abort | QMessageBox::Retry) == QMessageBox::Abort)
      return;
  }
  emit reservationSaved();
}

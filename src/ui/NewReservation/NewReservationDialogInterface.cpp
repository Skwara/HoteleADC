#include "NewReservationDialogInterface.h"

#include <QMessageBox>


NewReservationDialogInterface::NewReservationDialogInterface(QWidget* parent, ReservationPtr reservationToEdit)
  : QDialog(parent)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservationToEdit ? std::make_shared<Reservation>(*reservationToEdit) : std::make_shared<Reservation>())
  , _mainGroupBox(_reservation, this)
  , _roomsGroupBox(_reservation, this)
  , _participantsGroupBox(_reservation, this)
  , _additionalGroupBox(_reservation, this)
  , _summaryGroupBox(_reservation, this)
{
  connect(&_summaryGroupBox, SIGNAL(saveButtonClicked()), this, SLOT(onSaveButtonClicked()));

  this->resize(this->minimumWidth(), this->minimumHeight());
  setAttribute(Qt::WA_DeleteOnClose, true);
}

void NewReservationDialogInterface::connectToScheduleTableView(ScheduleTableView* view, NewReservationDialogInterface* dialog)
{
  connect(view, SIGNAL(roomSelectionChanged(QList<RoomPtr>)),
          dialog, SLOT(onScheduleRoomSelectionChanged(QList<RoomPtr>)));
  connect(view, SIGNAL(dateSelectionChanged(QPair<QDate,QDate>)),
          dialog, SLOT(onScheduleDateSelectionChanged(QPair<QDate,QDate>)));
  connect(dialog, SIGNAL(reservationSaved()), view, SLOT(updateSpan()));
}

void NewReservationDialogInterface::onScheduleRoomSelectionChanged(QList<RoomPtr> selectedRooms)
{
  _roomsGroupBox.update(selectedRooms);
}

NewReservationDialogInterface::~NewReservationDialogInterface()
{
}

void NewReservationDialogInterface::onSaveButtonClicked()
{
  if (!checkAvailability())
    return;
  if (!setClient())
    return;
  if (!saveReservation())
    return;
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

bool NewReservationDialogInterface::setClient()
{
  QList<ClientPtr> clients = _dbHandler->clients(_mainGroupBox.surname(), _mainGroupBox.name(), _mainGroupBox.street());
  if (clients.size() == 0)
    _reservation->setClient(_mainGroupBox.createClient());
  else if (clients.size() == 1)
    _reservation->setClient(clients.first());
  else
  {
    QMessageBox::critical(this, "Błąd", "Znaleziono więcej niż jednego klienta", QMessageBox::Ok);
    return false; // TODO handle selection of multiple clients
  }
  return true;
}

bool NewReservationDialogInterface::saveReservation()
{
  bool saved = false;
  while (!saved)
  {
    if (_dbHandler->saveReservation(_reservation))
      saved = true;
    else if (QMessageBox::critical(this, "Błąd", "Nie można zapisać rezerwacji", QMessageBox::Abort | QMessageBox::Retry) == QMessageBox::Abort)
      return false;
  }
  emit reservationSaved();
  return true;
}

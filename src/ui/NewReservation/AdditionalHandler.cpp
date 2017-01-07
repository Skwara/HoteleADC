#include "AdditionalHandler.h"
#include "ui_NewReservationDialog.h"


AdditionalHandler::AdditionalHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
{

}

void AdditionalHandler::setup()
{
  connect(ui->parkingCheckBox, SIGNAL(toggled(bool)), this, SLOT(onParkingCheckBoxToggled(bool)));
}

void AdditionalHandler::prepare()
{
  if (_dbHandler->hasAvailableParkingSpace(_reservation))
  {
    ui->parkingCheckBox->setEnabled(true);
    ui->parkingCheckBox->setChecked(_reservation.parking());
  }
}

void AdditionalHandler::onParkingCheckBoxToggled(bool checked)
{
  _reservation.setParking(checked);

  emit additionalChanged();
}

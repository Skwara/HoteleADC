#include "AdditionalHandler.h"
#include "ui_NewReservationDialog.h"


AdditionalHandler::AdditionalHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
{
  connect(&reservation, SIGNAL(dateChanged()), this, SLOT(update()));
}

void AdditionalHandler::setup()
{
  update();

  connect(ui->parkingCheckBox, SIGNAL(toggled(bool)), this, SLOT(onParkingCheckBoxToggled(bool)));
}

void AdditionalHandler::update()
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
}

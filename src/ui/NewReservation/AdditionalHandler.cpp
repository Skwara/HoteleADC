#include "AdditionalHandler.h"
#include "ui_NewSingleDialog.h"


AdditionalHandler::AdditionalHandler(Ui::NewSingleDialog* ui, ReservationPtr reservation, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
{
  connect(reservation.get(), SIGNAL(dateChanged()), this, SLOT(update()));
}

void AdditionalHandler::setup()
{
  update();

  connect(ui->parkingCheckBox, SIGNAL(toggled(bool)), this, SLOT(onParkingCheckBoxToggled(bool)));
  connect(ui->emptyPlaceCheckBox, SIGNAL(toggled(bool)), this, SLOT(onEmptyPlaceCheckBoxToggled(bool)));
}

void AdditionalHandler::update()
{
  if (_dbHandler->hasAvailableParkingSpace(_reservation))
  {
    ui->parkingCheckBox->setEnabled(true);
    ui->parkingCheckBox->setChecked(_reservation->parking());
  }

  ui->emptyPlaceCheckBox->setChecked(_reservation->countEmptyPlace());
}

void AdditionalHandler::onParkingCheckBoxToggled(bool checked)
{
  _reservation->setParking(checked);
}

void AdditionalHandler::onEmptyPlaceCheckBoxToggled(bool checked)
{
  _reservation->setCountEmptyPlace(checked);
}

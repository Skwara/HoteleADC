#include "AdditionalGroupBox.h"
#include "ui_AdditionalGroupBox.h"

AdditionalGroupBox::AdditionalGroupBox(ReservationPtr reservation, QWidget* parent)
  : QGroupBox(parent)
  , ui(new Ui::AdditionalGroupBox)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
{
  ui->setupUi(this);
  setup();
}

AdditionalGroupBox::~AdditionalGroupBox()
{
  delete ui;
}

void AdditionalGroupBox::update()
{
  if (_dbHandler->hasAvailableParkingSpace(_reservation))
  {
    ui->parkingCheckBox->setEnabled(true);
    ui->parkingCheckBox->setChecked(_reservation->parking());
  }

  ui->emptyPlaceCheckBox->setChecked(_reservation->countEmptyPlace());
}

void AdditionalGroupBox::setup()
{
  update();

  connect(_reservation.get(), SIGNAL(dateChanged()), this, SLOT(update()));
  connect(ui->parkingCheckBox, SIGNAL(toggled(bool)), this, SLOT(onParkingCheckBoxToggled(bool)));
  connect(ui->emptyPlaceCheckBox, SIGNAL(toggled(bool)), this, SLOT(onEmptyPlaceCheckBoxToggled(bool)));
}

void AdditionalGroupBox::onParkingCheckBoxToggled(bool checked)
{
  _reservation->setParking(checked);
}

void AdditionalGroupBox::onEmptyPlaceCheckBoxToggled(bool checked)
{
  _reservation->setCountEmptyPlace(checked);
}

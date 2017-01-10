#include "SummaryHandler.h"
#include "ui_NewReservationDialog.h"

SummaryHandler::SummaryHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
{
  connect(&reservation, SIGNAL(roomsChanged()), this, SLOT(update()));
  connect(&reservation, SIGNAL(participantsChanged()), this, SLOT(update()));
  connect(&reservation, SIGNAL(dateChanged()), this, SLOT(update()));
  connect(&reservation, SIGNAL(additionalChanged()), this, SLOT(update()));
}

void SummaryHandler::setup()
{
  update();
}

void SummaryHandler::update()
{
  setSummaryDays();
  setSummaryRooms();
  setSummaryParticipants();
  setSummaryPrice();
}

void SummaryHandler::setSummaryDays()
{
  ui->daysValueLabel->setText(QString::number(_reservation.days()));
}

void SummaryHandler::setSummaryRooms()
{
  ui->roomsValueLabel->setText(QString::number(_reservation.rooms().size()));
}

void SummaryHandler::setSummaryParticipants()
{
  ui->participantsValueLabel->setText(QString::number(_reservation.participantsCount()));
}

void SummaryHandler::setSummaryPrice()
{
  ui->priceValueLabel->setText(QString::number(_reservation.price()));
}

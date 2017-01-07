#include "SummaryHandler.h"
#include "ui_NewReservationDialog.h"

SummaryHandler::SummaryHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
{
}

void SummaryHandler::setup()
{
  prepare();
}

void SummaryHandler::prepare()
{
  setSummaryDays(_reservation.days());
  setSummaryPrice(_reservation.price());
}

void SummaryHandler::setSummaryDays(const int days)
{
  ui->daysValueLabel->setText(QString::number(days));
}

void SummaryHandler::setSummaryPrice(const int price)
{
  ui->priceValueLabel->setText(QString::number(price));
}

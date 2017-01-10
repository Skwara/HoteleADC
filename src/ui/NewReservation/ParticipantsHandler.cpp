#include "ParticipantsHandler.h"
#include "ui_NewReservationDialog.h"

ParticipantsHandler::ParticipantsHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
  , _participantsModel(reservation)
{
  connect(&_reservation, SIGNAL(roomsChanged()), this, SLOT(update()));
}

void ParticipantsHandler::setup()
{
  ui->participantCountSpinBox->setValue(_reservation.participantsCount());

  ui->participantTableView->setModel(&_participantsModel);

  ui->participantTableView->horizontalHeader()->setMinimumSectionSize(ui->participantTableView->minimumWidth() / 2 - 1);
  ui->participantTableView->horizontalHeader()->setMaximumSectionSize(ui->participantTableView->horizontalHeader()->minimumSectionSize());
  ui->participantTableView->horizontalHeader()->setFixedHeight(25);
  ui->participantTableView->resizeColumnsToContents();

  ui->participantTableView->verticalHeader()->hide();
  // TODO Add space for vertical scrolling bar

  connect(ui->participantCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onParticipantsCountSpinBoxValueChanged(int)));
}

void ParticipantsHandler::update()
{
  _participantsModel.layoutChanged();
}

void ParticipantsHandler::onParticipantsCountSpinBoxValueChanged(int value)
{
  _reservation.setParticipantsCount(value);
}

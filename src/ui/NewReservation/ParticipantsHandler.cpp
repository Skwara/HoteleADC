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
  ui->participantTableView->setModel(&_participantsModel);
  ui->participantTableView->setItemDelegate(&_participantsModel.delegate());

  ui->participantTableView->horizontalHeader()->setMinimumSectionSize(ui->participantTableView->minimumWidth() / 2 - 1);
  ui->participantTableView->horizontalHeader()->setMaximumSectionSize(ui->participantTableView->horizontalHeader()->minimumSectionSize());
  ui->participantTableView->horizontalHeader()->setFixedHeight(25);
  ui->participantTableView->resizeColumnsToContents();

  ui->participantTableView->verticalHeader()->hide();
  // TODO Add space for vertical scrolling bar
}

void ParticipantsHandler::update()
{
  _participantsModel.layoutChanged();
}

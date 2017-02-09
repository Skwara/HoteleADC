#include "ParticipantsHandler.h"
#include "ui_NewReservationDialog.h"

ParticipantsHandler::ParticipantsHandler(Ui::NewReservationDialog* ui, ReservationPtr reservation, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
  , _participantsModel(reservation)
{
  connect(_reservation.get(), SIGNAL(roomsChanged()), this, SLOT(update()));
}

void ParticipantsHandler::setup()
{
  ui->participantTableView->setModel(&_participantsModel);
  ui->participantTableView->setItemDelegate(&_participantsModel.delegate());

  ui->participantTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->participantTableView->horizontalHeader()->setFixedHeight(25);
  ui->participantTableView->resizeColumnsToContents();

  ui->participantTableView->verticalHeader()->hide();
}

void ParticipantsHandler::update()
{
  _participantsModel.layoutChanged();
}

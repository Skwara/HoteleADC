#include "ParticipantsHandler.h"
#include "ui_NewReservationDialog.h"

ParticipantsHandler::ParticipantsHandler(Ui::NewReservationDialog* ui, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
{
}

void ParticipantsHandler::setup()
{
}

void ParticipantsHandler::prepare()
{
}

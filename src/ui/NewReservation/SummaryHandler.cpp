#include "SummaryHandler.h"
#include "ui_NewReservationDialog.h"

SummaryHandler::SummaryHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
  , _summaryModel(reservation)
{
  connect(&reservation, SIGNAL(roomsChanged()), this, SLOT(update()));
  connect(&reservation, SIGNAL(participantsChanged()), this, SLOT(update()));
  connect(&reservation, SIGNAL(dateChanged()), this, SLOT(update()));
  connect(&reservation, SIGNAL(additionalChanged()), this, SLOT(update()));
}

void SummaryHandler::setup()
{
  ui->summaryTableView->setModel(&_summaryModel);
  ui->summaryTableView->horizontalHeader()->hide();
  ui->summaryTableView->verticalHeader()->hide();
  ui->summaryTableView->horizontalHeader()->setSectionResizeMode(_summaryModel.columnCount() - 1, QHeaderView::Stretch);

  update();
}

void SummaryHandler::update()
{
  _summaryModel.layoutChanged();
}

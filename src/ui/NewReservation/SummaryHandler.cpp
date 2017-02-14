#include "SummaryHandler.h"
#include "ui_NewReservationDialog.h"

SummaryHandler::SummaryHandler(Ui::NewReservationDialog* ui, ReservationPtr reservation, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
  , _summaryModel(reservation)
{
  connect(reservation.get(), SIGNAL(roomsChanged()), this, SLOT(update()));
  connect(reservation.get(), SIGNAL(participantsChanged()), this, SLOT(update()));
  connect(reservation.get(), SIGNAL(dateChanged()), this, SLOT(update()));
  connect(reservation.get(), SIGNAL(additionalChanged()), this, SLOT(update()));
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

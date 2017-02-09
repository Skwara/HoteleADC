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

  connect(ui->summarySaveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));

  update();
}

void SummaryHandler::update()
{
  _summaryModel.layoutChanged();
}

void SummaryHandler::onSaveButtonClicked()
{
  QList<ClientPtr> clients = _dbHandler->clients(ui->surnameLineEdit->text(), ui->nameLineEdit->text(), ui->streetLineEdit->text());
  if (clients.size() == 1)
  {
    _reservation->setClient(clients.first());
    if (!_dbHandler->saveReservation(_reservation))
    {
      // TODO handle error
    }
  }
  else
  {
    // TODO handle selection of multiple clients
  }
}

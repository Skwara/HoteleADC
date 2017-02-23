#include "SummaryGroupBox.h"
#include "ui_SummaryGroupBox.h"

SummaryGroupBox::SummaryGroupBox(ReservationPtr reservation, QWidget* parent)
  : QGroupBox(parent)
  , ui(new Ui::SummaryGroupBox)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
  , _summaryModel(reservation)
{
  ui->setupUi(this);
  setup();
}

SummaryGroupBox::~SummaryGroupBox()
{
  delete ui;
}

void SummaryGroupBox::update()
{
  _summaryModel.layoutChanged();
}

void SummaryGroupBox::setup()
{
  connect(ui->summarySaveButton, SIGNAL(clicked(bool)), this, SIGNAL(saveButtonClicked()));

  connect(_reservation.get(), SIGNAL(roomsChanged()), this, SLOT(update()));
  connect(_reservation.get(), SIGNAL(participantsChanged()), this, SLOT(update()));
  connect(_reservation.get(), SIGNAL(dateChanged()), this, SLOT(update()));
  connect(_reservation.get(), SIGNAL(additionalChanged()), this, SLOT(update()));

  ui->summaryTableView->setModel(&_summaryModel);
  ui->summaryTableView->horizontalHeader()->hide();
  ui->summaryTableView->verticalHeader()->hide();
  ui->summaryTableView->horizontalHeader()->setSectionResizeMode(_summaryModel.columnCount() - 1, QHeaderView::Stretch);
  ui->summaryTableView->setMinimumHeight(_summaryModel.rowCount() * ui->summaryTableView->rowHeight(0) + (2 * ui->summaryTableView->frameWidth()));

  update();
}

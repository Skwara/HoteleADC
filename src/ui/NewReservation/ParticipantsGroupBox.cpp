#include "ParticipantsGroupBox.h"
#include "ui_ParticipantsGroupBox.h"

ParticipantsGroupBox::ParticipantsGroupBox(ReservationPtr reservation, QWidget* parent)
  : QGroupBox(parent)
  , ui(new Ui::ParticipantsGroupBox)
  , _dataHandler(DataHandler::instance())
  , _reservation(reservation)
  , _participantsModel(reservation)
{
  ui->setupUi(this);
  setup();
}

ParticipantsGroupBox::~ParticipantsGroupBox()
{
  delete ui;
}

void ParticipantsGroupBox::update()
{
  _participantsModel.layoutChanged();
}

void ParticipantsGroupBox::setup()
{
  connect(_reservation.get(), SIGNAL(roomsChanged()), this, SLOT(update()));

  ui->participantTableView->setModel(&_participantsModel);
  ui->participantTableView->setItemDelegate(&_participantsModel.delegate());

  ui->participantTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->participantTableView->horizontalHeader()->setFixedHeight(25);
  ui->participantTableView->resizeColumnsToContents();

  ui->participantTableView->verticalHeader()->hide();

  update();
}

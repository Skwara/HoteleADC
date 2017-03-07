#include "NewBatchDialog.h"
#include "ui_NewBatchDialog.h"


NewBatchDialog::NewBatchDialog(QWidget *parent, ReservationPtr reservationToEdit)
  : NewReservationDialogInterface(parent, reservationToEdit)
  , ui(new Ui::NewBatchDialog)
  , _batchDateGroupBox(_reservation, this)
{
  ui->setupUi(this);
  setupHandlers();
}

NewBatchDialog::~NewBatchDialog()
{
  delete ui;
}

void NewBatchDialog::setupHandlers()
{
  ui->horizontalLayout_1->insertWidget(0, &_mainGroupBox);
  ui->horizontalLayout_1->insertWidget(1, &_roomsGroupBox);
  ui->horizontalLayout_1->insertWidget(2, &_participantsGroupBox);
  ui->horizontalLayout_1->insertWidget(3, &_additionalGroupBox);
  ui->horizontalLayout_2->insertWidget(0, &_batchDateGroupBox);
  ui->horizontalLayout_2->insertWidget(1, &_summaryGroupBox);
}

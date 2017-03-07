#include "NewSingleDialog.h"
#include "ui_NewSingleDialog.h"


NewSingleDialog::NewSingleDialog(QWidget* parent, ReservationPtr reservationToEdit)
  : NewReservationDialogInterface(parent, reservationToEdit)
  , ui(new Ui::NewSingleDialog)
  , _singleDateGroupBox(_reservation, this)
{
  ui->setupUi(this);
  setupHandlers();
}

NewSingleDialog::~NewSingleDialog()
{
  delete ui;
}

void NewSingleDialog::onScheduleDateSelectionChanged(QPair<QDate, QDate> selectedBeginEndDates)
{
  _singleDateGroupBox.update(selectedBeginEndDates);
}

void NewSingleDialog::setupHandlers()
{
  ui->horizontalLayout_1->insertWidget(0, &_mainGroupBox);
  ui->horizontalLayout_1->insertWidget(1, &_roomsGroupBox);
  ui->horizontalLayout_1->insertWidget(2, &_participantsGroupBox);
  ui->horizontalLayout_1->insertWidget(3, &_additionalGroupBox);
  ui->horizontalLayout_2->insertWidget(0, &_singleDateGroupBox);
  ui->horizontalLayout_2->insertWidget(1, &_summaryGroupBox);
}

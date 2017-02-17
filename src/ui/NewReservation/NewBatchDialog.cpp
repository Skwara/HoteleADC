#include "NewBatchDialog.h"
#include "ui_NewBatchDialog.h"

NewBatchDialog::NewBatchDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::NewBatchDialog)
{
  ui->setupUi(this);
}

NewBatchDialog::~NewBatchDialog()
{
  delete ui;
}

#include "src/ui/ScheduleDialog.h"
#include "ui_ScheduleDialog.h"



ScheduleDialog::ScheduleDialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::ScheduleDialog)
  , _scheduleTableView(new ScheduleTableView(this))
{
  ui->setupUi(this);
  ui->gridLayout->addWidget(_scheduleTableView, 0, 0, 1, 1);

  setAttribute(Qt::WA_DeleteOnClose, true);
}

ScheduleDialog::~ScheduleDialog()
{
  delete ui;
}

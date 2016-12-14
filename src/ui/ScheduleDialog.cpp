#include "src/ui/ScheduleDialog.h"
#include "ui_ScheduleDialog.h"

#include "src/data/ScheduleModel.h"
#include "src/ui/ScheduleView.h"


ScheduleDialog::ScheduleDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ScheduleDialog)
{
  ui->setupUi(this);

  ScheduleView* scheduleTableView = new ScheduleView(this);
  scheduleTableView->setObjectName(QStringLiteral("scheduleTableView"));
  scheduleTableView->setFrameShape(QFrame::Box);
  scheduleTableView->setLineWidth(0);
  scheduleTableView->setMidLineWidth(1);
  ui->gridLayout->addWidget(scheduleTableView, 0, 0, 1, 1);

  //TODO Remove 1 pixel move of contents to horizontal header
  scheduleTableView->setModel(new ScheduleModel());

  scheduleTableView->horizontalHeader()->setMinimumSectionSize(horizontalHeaderWidth);
  scheduleTableView->horizontalHeader()->setMaximumSectionSize(scheduleTableView->horizontalHeader()->minimumSectionSize());
  scheduleTableView->horizontalHeader()->setFixedHeight(horizontalHeaderHeight);
  scheduleTableView->horizontalHeader()->setStyleSheet("QHeaderView{ border: 0px; border-bottom: 1px solid lightgrey; border-left: 1px solid lightgrey; }");
  scheduleTableView->resizeColumnsToContents();

  scheduleTableView->verticalHeader()->setMinimumSectionSize(verticalHeaderHeight);
  scheduleTableView->verticalHeader()->setMaximumSectionSize(scheduleTableView->verticalHeader()->minimumSectionSize());
  scheduleTableView->verticalHeader()->setFixedWidth(verticalHeaderWidth);
  scheduleTableView->verticalHeader()->setStyleSheet("QHeaderView{ border: 0px; border-right: 1px solid lightgrey; border-top: 1px solid lightgrey; }");
  scheduleTableView->resizeRowsToContents();

  scheduleTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

ScheduleDialog::~ScheduleDialog()
{
  delete ui;
}

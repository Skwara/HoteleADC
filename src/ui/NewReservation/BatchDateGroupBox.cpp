#include "BatchDateGroupBox.h"
#include "ui_BatchDateGroupBox.h"


BatchDateGroupBox::BatchDateGroupBox(ReservationPtr reservation, QWidget* parent)
  : QGroupBox(parent)
  , ui(new Ui::BatchDateGroupBox)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
{
  ui->setupUi(this);
  setup();
}

BatchDateGroupBox::~BatchDateGroupBox()
{
  delete ui;
}

void BatchDateGroupBox::update()
{
  selectBatch(_reservation->batch());
}

void BatchDateGroupBox::update(QPair<QDate, QDate> selectedBeginEndDates)
{
  BatchPtr batch = _dbHandler->batchPeriod(selectedBeginEndDates.first, selectedBeginEndDates.second);
  if (!batch)
  {
    selectBatch(nullptr);
    return;
  }

  _reservation->setBatch(batch);
  update();
}

void BatchDateGroupBox::setup()
{
  ui->dateTableView->setModel(&_batchDateModel);
  ui->dateTableView->verticalHeader()->hide();
  for (int col = 0; col < _batchDateModel.columnCount() - 1; ++col)
    ui->dateTableView->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Stretch);
  ui->dateTableView->horizontalHeader()->setSectionResizeMode(_batchDateModel.columnCount() - 1, QHeaderView::ResizeToContents);
  ui->dateTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->dateTableView->setSelectionMode(QAbstractItemView::SingleSelection);

  connect(ui->dateTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(onDateTableViewClicked(QModelIndex)));

  update();
}

void BatchDateGroupBox::selectBatch(BatchPtr batch)
{
  for (int row = 0; row < _batchDateModel.rowCount(); ++row)
    if (batch == _batchDateModel.sourceBatch(row))
      ui->dateTableView->selectionModel()->select(_batchDateModel.index(row, 0), QItemSelectionModel::Select | QItemSelectionModel::Rows);
    else
      ui->dateTableView->selectionModel()->select(_batchDateModel.index(row, 0), QItemSelectionModel::Deselect | QItemSelectionModel::Rows);
}

void BatchDateGroupBox::onDateTableViewClicked(const QModelIndex& index)
{
  _reservation->setBatch(_batchDateModel.sourceBatch(index.row()));
}

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

void BatchDateGroupBox::update(QSet<int> selectedCols)
{
  // TODO Remove this method. Save dates earlier in reservation and use update() based on reservation.
  std::pair<QSet<int>::const_iterator, QSet<int>::const_iterator> beginEndCol = std::minmax_element(selectedCols.begin(), selectedCols.end());
  QDate beginDate = _dbHandler->firstDate().addDays(*beginEndCol.first);
  QDate endDate = _dbHandler->firstDate().addDays(*beginEndCol.second + 1); // On schedule leave date is not selected

  BatchPtr batch = _dbHandler->batchPeriod(beginDate, endDate);
  if (batch)
  {
    _reservation->setBatch(batch);
    update();
  }
}

void BatchDateGroupBox::update()
{
  for (int row = 0; row < _batchDateModel.rowCount(); ++row)
  {
    if (_reservation->batch() == _batchDateModel.sourceBatch(row))
    {
      ui->dateTableView->selectionModel()->select(_batchDateModel.index(row, 0), QItemSelectionModel::Select | QItemSelectionModel::Rows);
    }
  }
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

void BatchDateGroupBox::onDateTableViewClicked(const QModelIndex& index)
{
  _reservation->setBatch(_batchDateModel.sourceBatch(index.row()));
}

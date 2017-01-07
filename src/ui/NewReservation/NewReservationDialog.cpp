#include "NewReservationDialog.h"
#include "ui_NewReservationDialog.h"


NewReservationDialog::NewReservationDialog(QWidget* parent)
  : QDialog(parent)
  , ui(new Ui::NewReservationDialog)
  , _reservation()
  , _dbHandler(DatabaseHandler::instance())
  , _main(ui, this)
  , _participants(ui, this)
  , _rooms(ui, _reservation, this)
  , _date(ui, _reservation, this)
  , _additional(ui, _reservation, this)
{
  ui->setupUi(this);
  _main.setup();
  _participants.setup();
  _rooms.setup();
  _date.setup();
  _additional.setup();

  _main.prepare();
  _participants.prepare();
  _rooms.prepare();
  _date.prepare();
  _additional.prepare();
  prepareSummary();

  setAttribute(Qt::WA_DeleteOnClose, true);
}

NewReservationDialog::~NewReservationDialog()
{
  delete ui;
}

void NewReservationDialog::scheduleSelectionChanged(const QItemSelection& /*selected*/, const QItemSelection& /*deselected*/)
{
  QItemSelectionModel* selectionModel = qobject_cast<QItemSelectionModel*>(sender());
  QSet<QModelIndex> allSelected = selectionModel->selectedIndexes().toSet();
  QSet<int> selectedRows;
  foreach (QModelIndex index, allSelected)
  {
    selectedRows += index.row();
  }

  QAbstractItemModel* model = ui->roomListView->model();
  for (int i = 0; i < ui->roomListView->model()->rowCount(); ++i)
  {
    if (selectedRows.contains(i) && !ui->roomListView->selectionModel()->isRowSelected(i, QModelIndex()))
    {
      ui->roomListView->selectionModel()->select(model->index(i, 0), QItemSelectionModel::Select);
    }
    else if (!selectedRows.contains(i) && ui->roomListView->selectionModel()->isRowSelected(i, QModelIndex()))
    {
      ui->roomListView->selectionModel()->select(model->index(i, 0), QItemSelectionModel::Deselect);
    }
  }

  std::pair<QSet<QModelIndex>::iterator, QSet<QModelIndex>::iterator> beginEndCol = std::minmax_element(allSelected.begin(), allSelected.end(),
    [](const QModelIndex& left, const QModelIndex& right)
    {
      return left.column() < right.column();
    });
  QDate beginDate = _dbHandler->firstDate().addDays(beginEndCol.first->column());
  QDate endDate = _dbHandler->firstDate().addDays(beginEndCol.second->column() + 1); // On schedule leave date is not selected
  _reservation.setBeginDate(beginDate);
  _reservation.setEndDate(endDate);
  ui->beginCalendarWidget->setSelectedDate(beginDate);
  ui->endCalendarWidget->setSelectedDate(endDate);

  prepareSummary();
}

void NewReservationDialog::prepareSummary()
{
  setSummaryDays(_reservation.days());
  setSummaryPrice(_reservation.price());
}

void NewReservationDialog::setSummaryDays(const int days)
{
  ui->daysValueLabel->setText(QString::number(days));
}

void NewReservationDialog::setSummaryPrice(const int price)
{
  ui->priceValueLabel->setText(QString::number(price));
}

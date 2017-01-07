#include "NewReservationDialog.h"
#include "ui_NewReservationDialog.h"

#include "src/data/RoomsModel.h"


NewReservationDialog::NewReservationDialog(QWidget* parent)
  : QDialog(parent)
  , ui(new Ui::NewReservationDialog)
  , _reservation()
  , _dbHandler(DatabaseHandler::instance())
  , _main(ui, this)
{
  ui->setupUi(this);
  _main.setup();

  _main.prepare();
  prepareParticipants();
  prepareRoom();
  prepareDate();
  prepareAdditional();
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
  ui->beginCalendarWidget->setSelectedDate(beginDate);
  ui->endCalendarWidget->setSelectedDate(endDate);

  prepareSummary();
}

void NewReservationDialog::prepareParticipants()
{

}

void NewReservationDialog::prepareRoom()
{
  ui->roomListView->setModel(RoomsModel::instance());
  ui->roomListView->setSelectionMode(QAbstractItemView::ExtendedSelection);

  connect(ui->roomListView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onRoomListViewSelectionChanged(QItemSelection,QItemSelection)));
}

void NewReservationDialog::prepareDate()
{
  QDate currentDate = QDate::currentDate();
  _reservation.setBeginDate(currentDate);
  ui->beginCalendarWidget->setSelectedDate(currentDate);
  _reservation.setEndDate(currentDate);
  ui->endCalendarWidget->setSelectedDate(currentDate);
}

void NewReservationDialog::prepareAdditional()
{
  if (_dbHandler->hasAvailableParkingSpace(_reservation))
  {
    ui->parkingCheckBox->setEnabled(true);
    ui->parkingCheckBox->setChecked(_reservation.parking());
  }
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

void NewReservationDialog::setEndDateToBeginDate()
{
  QDate beginDate = _reservation.beginDate();
  _reservation.setEndDate(beginDate);
  ui->endCalendarWidget->setSelectedDate(beginDate);
}

void NewReservationDialog::on_beginCalendarWidget_clicked(const QDate &date)
{
  _reservation.setBeginDate(date);
  if (date > _reservation.endDate())
  {
    setEndDateToBeginDate();
  }

  prepareSummary();
}

void NewReservationDialog::on_endCalendarWidget_clicked(const QDate &date)
{
  if (date >= _reservation.beginDate())
  {
    _reservation.setEndDate(date);
  }
  else
  {
    setEndDateToBeginDate();
  }

  prepareSummary();
}

void NewReservationDialog::on_addParticipantPushButton_clicked()
{
  // TODO Enable addButton only if both fields are not empty
  QString surname = ui->participantSurnameLineEdit->text();
  QString name = ui->participantNameLineEdit->text();
  QString participant = surname + " " + name;
  if (!surname.isEmpty() && !name.isEmpty())
  {
    ui->participantsListWidget->addItem(participant);
    ui->participantSurnameLineEdit->clear();
    ui->participantNameLineEdit->clear();
    _reservation.addParticipant(participant);
    prepareSummary();
  }
}

void NewReservationDialog::on_parkingCheckBox_toggled(bool checked)
{
  _reservation.setParking(checked);
  prepareSummary();
}

void NewReservationDialog::onRoomListViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
  foreach (QModelIndex index, selected.indexes())
  {
    RoomPtr room = _dbHandler->room(ui->roomListView->model()->data(index).toInt());
    _reservation.addRoom(room);
  }

  foreach (QModelIndex index, deselected.indexes())
  {
    RoomPtr room = _dbHandler->room(ui->roomListView->model()->data(index).toInt());
    _reservation.removeRoom(room);
  }
}

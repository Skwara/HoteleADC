#include "NewReservationDialog.h"
#include "ui_NewReservationDialog.h"

#include <QCompleter>

#include "src/data/RoomsModel.h"


NewReservationDialog::NewReservationDialog(QWidget* parent)
  : QDialog(parent)
  , ui(new Ui::NewReservationDialog)
  , _reservation()
  , _dbHandler(DatabaseHandler::instance())
{
  ui->setupUi(this);

  prepareMain();
  prepareParticipants();
  prepareRoom();
  prepareDate();
  prepareSummary();

  setAttribute(Qt::WA_DeleteOnClose, true);
}

NewReservationDialog::~NewReservationDialog()
{
  delete ui;
}

void NewReservationDialog::scheduleSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
  static QSet<QModelIndex> allSelected;
  allSelected -= deselected.indexes().toSet();
  allSelected += selected.indexes().toSet();
  ui->roomListView->selectionModel()->clear();
  QAbstractItemModel* model = ui->roomListView->model();
  foreach (QModelIndex index, allSelected)
  {
    ui->roomListView->selectionModel()->select(model->index(index.row(), 0), QItemSelectionModel::Select);
  }

  std::pair<QSet<QModelIndex>::iterator, QSet<QModelIndex>::iterator> beginEndCol = std::minmax_element(allSelected.begin(), allSelected.end(),
    [](const QModelIndex& left, const QModelIndex& right)
    {
      return left.column() < right.column();
    });
  QDate beginDate = _dbHandler->firstDate().addDays(beginEndCol.first->column());
  QDate endDate = _dbHandler->firstDate().addDays(beginEndCol.second->column());
  ui->beginCalendarWidget->setSelectedDate(beginDate);
  ui->endCalendarWidget->setSelectedDate(endDate);
}

void NewReservationDialog::prepareMain()
{
  QSet<QString> surnames;
  foreach (Client client, _dbHandler->clients())
  {
    surnames << client.surname();
  }
  addCompleter(ui->surnameLineEdit, surnames);
}

void NewReservationDialog::prepareParticipants()
{

}

void NewReservationDialog::prepareRoom()
{
  ui->roomListView->setModel(RoomsModel::instance());
  ui->roomListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void NewReservationDialog::prepareDate()
{
  QDate currentDate = QDate::currentDate();
  _reservation.setBeginDate(currentDate);
  ui->beginCalendarWidget->setSelectedDate(currentDate);
  _reservation.setEndDate(currentDate);
  ui->endCalendarWidget->setSelectedDate(currentDate);
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

void NewReservationDialog::addCompleter(QLineEdit* lineEdit, QSet<QString> completions)
{
  if (completions.isEmpty())
    return;

  if (completions.size() == 1)
  {
    lineEdit->setText(*completions.begin());
  }

  QCompleter* completer = new QCompleter(completions.toList(), this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  completer->setFilterMode(Qt::MatchContains);
  lineEdit->setCompleter(completer);
}

void NewReservationDialog::fillRemainingClientData(QString surname, QString name, QString street)
{
  QList<Client> matchingClients  = _dbHandler->clients(surname, name, street);
  QSet<QString> names;
  QSet<QString> streets;
  foreach (Client client, matchingClients)
  {
    names << client.name();
    streets << client.address().street();
  }
  if (name.isEmpty())
  {
    addCompleter(ui->nameLineEdit, names);
  }
  if (name.isEmpty() && street.isEmpty())
  {
    addCompleter(ui->streetLineEdit, streets);
  }

  if (matchingClients.size() == 1)
  {
    const Client& client = matchingClients.first();
    ui->surnameLineEdit->setText(client.surname());
    ui->nameLineEdit->setText(client.name());
    ui->streetLineEdit->setText(client.address().street());
    ui->numberLineEdit->setText(client.address().number());
    ui->postalCodeLineEdit->setText(client.address().postalCode());
    ui->cityLineEdit->setText(client.address().city());
    ui->countryLineEdit->setText(client.address().country());
    ui->phoneLineEdit->setText(client.phone());
    ui->emailLineEdit->setText(client.eMail());
  }
}

void NewReservationDialog::on_beginCalendarWidget_clicked(const QDate& date)
{
  _reservation.setBeginDate(date);
  if (date > _reservation.endDate())
  {
    setEndDateToBeginDate();
  }

  prepareSummary();
}

void NewReservationDialog::on_endCalendarWidget_clicked(const QDate& date)
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

void NewReservationDialog::on_surnameLineEdit_editingFinished()
{
  QString surname = ui->surnameLineEdit->text();
  if (!surname.isEmpty())
  {
    Client::firstLetterUppercase(surname);
    ui->surnameLineEdit->setText(surname);
    fillRemainingClientData(surname);
  }
}

void NewReservationDialog::on_nameLineEdit_editingFinished()
{
  QString surname = ui->surnameLineEdit->text();
  QString name = ui->nameLineEdit->text();
  if (!name.isEmpty())
  {
    Client::firstLetterUppercase(name);
    ui->nameLineEdit->setText(name);
    fillRemainingClientData(surname, name);
  }
}

void NewReservationDialog::on_streetLineEdit_editingFinished()
{
  QString surname = ui->surnameLineEdit->text();
  QString name = ui->nameLineEdit->text();
  QString street = ui->streetLineEdit->text();
  if (!street.isEmpty())
  {
    Address::correctStreetFormatting(street);
    ui->streetLineEdit->setText(street);
    fillRemainingClientData(surname, name, street);
  }
}

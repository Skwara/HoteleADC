#include "NewReservationDialog.h"
#include "ui_NewReservationDialog.h"

#include <QCompleter>

NewReservationDialog::NewReservationDialog(DatabaseHandler& dbHandler, QWidget* parent)
  : QDialog(parent)
  , ui(new Ui::NewReservationDialog)
  , _reservation()
  , _dbHandler(dbHandler)
{
  ui->setupUi(this);

  prepareMain();
  prepareDate();
  prepareParticipants();
  prepareSummary();
}

NewReservationDialog::~NewReservationDialog()
{
  delete ui;
}

void NewReservationDialog::prepareMain()
{
  QSet<QString> surnames;
  QSet<QString> names;
  foreach (Client client, _dbHandler.clients())
  {
    surnames << client.surname();
    names << client.name();
  }

  QCompleter* surnameCompleter = new QCompleter(surnames.toList(), this);
  surnameCompleter->setCaseSensitivity(Qt::CaseInsensitive);
  surnameCompleter->setFilterMode(Qt::MatchContains);
  ui->surnameLineEdit->setCompleter(surnameCompleter);

  QCompleter* nameCompleter = new QCompleter(names.toList(), this);
  nameCompleter->setCaseSensitivity(Qt::CaseInsensitive);
  nameCompleter->setFilterMode(Qt::MatchContains);
  ui->nameLineEdit->setCompleter(nameCompleter);
}

void NewReservationDialog::prepareDate()
{
  QDate currentDate = QDate::currentDate();
  _reservation.setBeginDate(currentDate);
  ui->beginCalendarWidget->setSelectedDate(currentDate);
  _reservation.setEndDate(currentDate);
  ui->endCalendarWidget->setSelectedDate(currentDate);
}

void NewReservationDialog::prepareParticipants()
{

}

void NewReservationDialog::prepareSummary()
{
  setSummaryDays(_reservation.days());
}

void NewReservationDialog::setSummaryDays(int days)
{
  ui->daysValueLabel->setText(QString::number(days));
}

void NewReservationDialog::setEndDateToBeginDate()
{
  QDate beginDate = _reservation.beginDate();
  _reservation.setEndDate(beginDate);
  ui->endCalendarWidget->setSelectedDate(beginDate);
}

void NewReservationDialog::on_beginCalendarWidget_clicked(const QDate& date)
{
  _reservation.setBeginDate(date);
  if (date > _reservation.endDate())
  {
    setEndDateToBeginDate();
  }

  setSummaryDays(_reservation.days());
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

  setSummaryDays(_reservation.days());
}

void NewReservationDialog::on_addParticipantPushButton_clicked()
{
  // TODO Enable addButton only if both fields are not empty
  QString surname = ui->participantSurnameLineEdit->text();
  QString name = ui->participantNameLineEdit->text();
  if (!surname.isEmpty() && !name.isEmpty())
  {
    ui->participantsListWidget->addItem(surname + " " + name);
    ui->participantSurnameLineEdit->clear();
    ui->participantNameLineEdit->clear();
  }
}

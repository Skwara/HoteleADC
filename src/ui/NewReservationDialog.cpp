#include "NewReservationDialog.h"
#include "ui_NewReservationDialog.h"

NewReservationDialog::NewReservationDialog(QWidget* parent) :
  QDialog(parent),
  ui(new Ui::NewReservationDialog)
{
  ui->setupUi(this);

  reservation.setBeginDate(QDate::currentDate());
  ui->beginCalendarWidget->setSelectedDate(QDate::currentDate());
  reservation.setEndDate(QDate::currentDate());
  ui->endCalendarWidget->setSelectedDate(QDate::currentDate());
  setSummaryDays(reservation.getDays());
}

NewReservationDialog::~NewReservationDialog()
{
  delete ui;
}

void NewReservationDialog::setSummaryDays(int days)
{
  ui->daysValueLabel->setText(QString::number(days));
}

void NewReservationDialog::setEndDateToBeginDate()
{
  QDate beginDate = reservation.getBeginDate();
  reservation.setEndDate(beginDate);
  ui->endCalendarWidget->setSelectedDate(beginDate);
}

void NewReservationDialog::on_beginCalendarWidget_clicked(const QDate& date)
{
  reservation.setBeginDate(date);
  if (date > reservation.getEndDate())
  {
    setEndDateToBeginDate();
  }

  setSummaryDays(reservation.getDays());
}

void NewReservationDialog::on_endCalendarWidget_clicked(const QDate& date)
{
  if (date >= reservation.getBeginDate())
  {
    reservation.setEndDate(date);
  }
  else
  {
    setEndDateToBeginDate();
  }

  setSummaryDays(reservation.getDays());
}

#include "DateHandler.h"
#include "ui_NewReservationDialog.h"


DateHandler::DateHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
{
}

void DateHandler::setup()
{
  QDate currentDate = QDate::currentDate();
  _reservation.setBeginDate(currentDate);
  ui->beginCalendarWidget->setSelectedDate(currentDate);
  _reservation.setEndDate(currentDate);
  ui->endCalendarWidget->setSelectedDate(currentDate);

  connect(ui->beginCalendarWidget, SIGNAL(clicked(QDate)), this, SLOT(onBeginCalendarWidgetClicked(QDate)));
  connect(ui->endCalendarWidget, SIGNAL(clicked(QDate)), this, SLOT(onEndCalendarWidgetClicked(QDate)));
}

void DateHandler::prepare()
{
}

void DateHandler::onBeginCalendarWidgetClicked(const QDate& date)
{
  _reservation.setBeginDate(date);
  if (date > _reservation.endDate())
  {
    setEndDateToBeginDate();
  }

  emit dateChanged();
}

void DateHandler::onEndCalendarWidgetClicked(const QDate& date)
{
  if (date >= _reservation.beginDate())
  {
    _reservation.setEndDate(date);
  }
  else
  {
    setEndDateToBeginDate();
  }

  emit dateChanged();
}

void DateHandler::setEndDateToBeginDate()
{
  QDate beginDate = _reservation.beginDate();
  _reservation.setEndDate(beginDate);
  ui->endCalendarWidget->setSelectedDate(beginDate);
}

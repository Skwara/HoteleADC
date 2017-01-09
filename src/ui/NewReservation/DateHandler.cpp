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

void DateHandler::update(QSet<int> selectedCols)
{
  std::pair<QSet<int>::const_iterator, QSet<int>::const_iterator> beginEndCol = std::minmax_element(selectedCols.begin(), selectedCols.end());
  QDate beginDate = _dbHandler->firstDate().addDays(*beginEndCol.first);
  QDate endDate = _dbHandler->firstDate().addDays(*beginEndCol.second + 1); // On schedule leave date is not selected

  _reservation.setBeginDate(beginDate);
  _reservation.setEndDate(endDate);
  ui->beginCalendarWidget->setSelectedDate(beginDate);
  ui->endCalendarWidget->setSelectedDate(endDate);
}

void DateHandler::onBeginCalendarWidgetClicked(const QDate& date)
{
  _reservation.setBeginDate(date);
  if (date > _reservation.endDate())
  {
    setEndDateToBeginDate();
  }
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
}

void DateHandler::setEndDateToBeginDate()
{
  QDate beginDate = _reservation.beginDate();
  _reservation.setEndDate(beginDate);
  ui->endCalendarWidget->setSelectedDate(beginDate);
}

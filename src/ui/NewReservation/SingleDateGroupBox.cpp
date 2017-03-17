#include "SingleDateGroupBox.h"
#include "ui_SingleDateGroupBox.h"

SingleDateGroupBox::SingleDateGroupBox(ReservationPtr reservation, QWidget* parent)
  : QGroupBox(parent)
  , ui(new Ui::SingleDateGroupBox)
  , _dataHandler(DataHandler::instance())
  , _reservation(reservation)
{
  ui->setupUi(this);
  setup();
}

SingleDateGroupBox::~SingleDateGroupBox()
{
  delete ui;
}

void SingleDateGroupBox::update()
{
  ui->beginCalendarWidget->setSelectedDate(_reservation->beginDate());
  ui->endCalendarWidget->setSelectedDate(_reservation->endDate());
}

void SingleDateGroupBox::update(QPair<QDate, QDate> beginEndDates)
{
  _reservation->setBeginDate(beginEndDates.first);
  _reservation->setEndDate(beginEndDates.second);
  update();
}

void SingleDateGroupBox::setup()
{
  connect(ui->beginCalendarWidget, SIGNAL(clicked(QDate)), this, SLOT(onBeginCalendarWidgetClicked(QDate)));
  connect(ui->endCalendarWidget, SIGNAL(clicked(QDate)), this, SLOT(onEndCalendarWidgetClicked(QDate)));

  update();
}

void SingleDateGroupBox::onBeginCalendarWidgetClicked(const QDate& date)
{
  _reservation->setBeginDate(date);
  if (date > _reservation->endDate())
  {
    setEndDateToBeginDate();
  }
}

void SingleDateGroupBox::onEndCalendarWidgetClicked(const QDate& date)
{
  if (date >= _reservation->beginDate())
  {
    _reservation->setEndDate(date);
  }
  else
  {
    setEndDateToBeginDate();
  }
}

void SingleDateGroupBox::setEndDateToBeginDate()
{
  QDate beginDate = _reservation->beginDate();
  _reservation->setEndDate(beginDate);
  ui->endCalendarWidget->setSelectedDate(beginDate);
}

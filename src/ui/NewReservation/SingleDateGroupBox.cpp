#include "SingleDateGroupBox.h"
#include "ui_SingleDateGroupBox.h"

SingleDateGroupBox::SingleDateGroupBox(ReservationPtr reservation, QWidget* parent)
  : QGroupBox(parent)
  , ui(new Ui::SingleDateGroupBox)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
{
  ui->setupUi(this);
  setup();
}

SingleDateGroupBox::~SingleDateGroupBox()
{
  delete ui;
}

void SingleDateGroupBox::update(QSet<int> selectedCols)
{
  // TODO Remove this method. Save dates earlier in reservation and use update() based on reservation.
  std::pair<QSet<int>::const_iterator, QSet<int>::const_iterator> beginEndCol = std::minmax_element(selectedCols.begin(), selectedCols.end());
  QDate beginDate = _dbHandler->firstDate().addDays(*beginEndCol.first);
  QDate endDate = _dbHandler->firstDate().addDays(*beginEndCol.second + 1); // On schedule leave date is not selected

  _reservation->setBeginDate(beginDate);
  _reservation->setEndDate(endDate);
  update();
}

void SingleDateGroupBox::update()
{
  ui->beginCalendarWidget->setSelectedDate(_reservation->beginDate());
  ui->endCalendarWidget->setSelectedDate(_reservation->endDate());
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

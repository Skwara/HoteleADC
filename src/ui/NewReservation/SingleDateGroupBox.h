#ifndef SINGLEDATEGROUPBOX_H
#define SINGLEDATEGROUPBOX_H

#include <QGroupBox>

#include "data/DataHandler.h"


namespace Ui {
class SingleDateGroupBox;
}

class SingleDateGroupBox : public QGroupBox
{
  Q_OBJECT

public:
  explicit SingleDateGroupBox(ReservationPtr reservation, QWidget* parent = 0);
  ~SingleDateGroupBox();

public slots:
  void update();
  void update(QPair<QDate, QDate> beginEndDates);

private:
  void setup();

private slots:
  void onBeginCalendarWidgetClicked(const QDate &date);
  void onEndCalendarWidgetClicked(const QDate &date);
private:
  void setEndDateToBeginDate();

private:
  Ui::SingleDateGroupBox* ui;
  DataHandler* _dataHandler;

  ReservationPtr _reservation;
};

#endif // SINGLEDATEGROUPBOX_H

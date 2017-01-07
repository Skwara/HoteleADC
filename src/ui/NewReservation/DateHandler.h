#ifndef DATEHANDLER_H
#define DATEHANDLER_H

#include <QObject>

#include "data/DatabaseHandler.h"


namespace Ui {
class NewReservationDialog;
}

class DateHandler : public QObject
{
  Q_OBJECT

public:
  explicit DateHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent = 0);

  void setup();
  void prepare();

signals:
  void dateChanged();

private slots:
  void onBeginCalendarWidgetClicked(const QDate &date);
  void onEndCalendarWidgetClicked(const QDate &date);

private:
  void setEndDateToBeginDate();

private:
  Ui::NewReservationDialog* ui;
  DatabaseHandler* _dbHandler;

  Reservation& _reservation;
};

#endif // DATEHANDLER_H

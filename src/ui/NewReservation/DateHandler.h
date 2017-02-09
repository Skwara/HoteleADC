#ifndef DATEHANDLER_H
#define DATEHANDLER_H

#include <QObject>

#include "data/DatabaseHandler.h"


namespace Ui {
class NewReservationDialog;
}

using BeginEndDates = std::pair<QDate, QDate>;

class DateHandler : public QObject
{
  Q_OBJECT

public:
  explicit DateHandler(Ui::NewReservationDialog* ui, ReservationPtr reservation, QObject* parent = 0);

  void setup();

public slots:
  void update(QSet<int> selectedCols);

private slots:
  void onBeginCalendarWidgetClicked(const QDate &date);
  void onEndCalendarWidgetClicked(const QDate &date);

private:
  void setEndDateToBeginDate();

private:
  Ui::NewReservationDialog* ui;
  DatabaseHandler* _dbHandler;

  ReservationPtr _reservation;
};

#endif // DATEHANDLER_H

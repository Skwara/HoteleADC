#ifndef DATEHANDLER_H
#define DATEHANDLER_H

#include <QObject>

#include "data/DatabaseHandler.h"


namespace Ui {
class NewSingleDialog;
}

using BeginEndDates = std::pair<QDate, QDate>;

class DateHandler : public QObject
{
  Q_OBJECT

public:
  explicit DateHandler(Ui::NewSingleDialog* ui, ReservationPtr reservation, QObject* parent = 0);

  void setup();

public slots:
  void update(QSet<int> selectedCols);

private slots:
  void onBeginCalendarWidgetClicked(const QDate &date);
  void onEndCalendarWidgetClicked(const QDate &date);

private:
  void setEndDateToBeginDate();

private:
  Ui::NewSingleDialog* ui;
  DatabaseHandler* _dbHandler;

  ReservationPtr _reservation;
};

#endif // DATEHANDLER_H

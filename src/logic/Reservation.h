#ifndef RESERVATION_H
#define RESERVATION_H

#include <QDate>

class Reservation
{
public:
  Reservation();

  QDate getBeginDate() const { return beginDate; }
  QDate getEndDate() const { return endDate; }
  int getDays() const { return beginDate.daysTo(endDate); }

  void setBeginDate(const QDate& date) { beginDate = date; }
  void setEndDate(const QDate& date) { endDate = date; }

private:
  QDate beginDate;
  QDate endDate;
};

#endif // RESERVATION_H

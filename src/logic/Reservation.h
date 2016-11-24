#ifndef RESERVATION_H
#define RESERVATION_H

#include <QDate>

class Reservation
{
public:
  Reservation();

  QDate beginDate() const { return _beginDate; }
  QDate endDate() const { return _endDate; }
  int days() const { return _beginDate.daysTo(_endDate); }

  void setBeginDate(const QDate& date) { _beginDate = date; }
  void setEndDate(const QDate& date) { _endDate = date; }

private:
  QDate _beginDate;
  QDate _endDate;
};

#endif // RESERVATION_H

#include "Reservation.h"
#include "data/DatabaseHandler.h"

Reservation::Reservation()
  : _client(nullptr)
  , _room(nullptr)
  , _parking(false)
{
}

int Reservation::price() const
{
  DatabaseHandler* dbHandler = DatabaseHandler::instance();
  int price = 0;
  QDate currentDate = _beginDate;
  while (currentDate < _endDate)
  {
    price += dbHandler->roomCost(currentDate);
    if (_parking)
    {
      price += dbHandler->parkingCost(currentDate);
    }
    currentDate = currentDate.addDays(1);
  }

  price *= _participants.length() + 1;

  return price;
}

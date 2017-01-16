#include "Price.h"

#include "data/DatabaseHandler.h"


Price::Price(QDate beginDate, QDate endDate, QMap<RoomPtr, int> rooms, bool parking, bool countEmptyPlace)
  : _parkingPrice(0)
  , _beginDate(beginDate)
  , _endDate(endDate)
  , _rooms(rooms)
  , _parking(parking)
  , _countEmptyPlace(countEmptyPlace)
{
  calculatePrice();
}

int Price::fullPrice() const
{
  int price = 0;
  foreach (RoomPtr room, _rooms.keys())
  {
    price += _roomParticipantsPrices[room];
    price += _roomEmptyPlacePrices[room];
  }

  if (_parking)
  {
    price += _parkingPrice;
  }

  return price;
}

void Price::calculatePrice()
{
  QDate currentDate = _beginDate;
  while (currentDate < _endDate)
  {
    addRoomsPrice(currentDate);
    if (_parking)
    {
      addParkingPrice(currentDate);
    }

    currentDate = currentDate.addDays(1);
  }
}

void Price::addRoomsPrice(QDate currentDate)
{
  foreach (RoomPtr room, _rooms.keys())
  {
    _roomParticipantsPrices[room] += DatabaseHandler::instance()->roomCost(currentDate) * _rooms[room];
    if (_countEmptyPlace)
    {
      addEmptyPlacePrice(currentDate, room);
    }
  }
}

void Price::addEmptyPlacePrice(QDate currentDate, RoomPtr room)
{
  int roomEmptyPlaceCount = room->maxParticipants() - _rooms[room];
  if (roomEmptyPlaceCount > 0)
  {
    _roomEmptyPlacePrices[room] += DatabaseHandler::instance()->emptyPlaceCost(currentDate) * roomEmptyPlaceCount;
  }
}

void Price::addParkingPrice(QDate currentDate)
{
  _parkingPrice += DatabaseHandler::instance()->parkingCost(currentDate);
}

#include "Price.h"

#include "data/DatabaseHandler.h"


// TODO Refactoring with SummaryModel class
Price::Price(QDate beginDate, QDate endDate, QMap<RoomPtr, QPair<int, int>> rooms, bool parking, bool countEmptyPlace)
  : _parkingPrice(0)
  , _beginDate(beginDate)
  , _endDate(endDate)
  , _rooms(rooms)
  , _parking(parking)
  , _countEmptyPlace(countEmptyPlace)
{
  calculatePrice();
}

void Price::update(QDate beginDate, QDate endDate, QMap<RoomPtr, QPair<int, int> > rooms, bool parking, bool countEmptyPlace)
{
  _roomParticipantsPrices.clear();
  _roomEmptyPlacePrices.clear();
  _roomAdditionalParticipantsPrices.clear();
  _parkingPrice = 0;
  _beginDate = beginDate;
  _endDate = endDate;
  _rooms = rooms;
  _parking = parking;
  _countEmptyPlace = countEmptyPlace;
  calculatePrice();
}

PricePair Price::roomsPrice() const
{
  int calculated = roomsCalculatedPrice();
  bool hasManual = _manualRoomsPrice >= 0;
  return PricePair(calculated, hasManual ? _manualRoomsPrice : calculated, hasManual);
}

PricePair Price::roomsEmptyPlacePrice() const
{
  int calculated = roomsCalculatedEmptyPlacePrice();
  bool hasManual = _manualRoomsEmptyPlacePrice >= 0;
  return PricePair(calculated, hasManual ? _manualRoomsEmptyPlacePrice : calculated, hasManual);
}

PricePair Price::roomsAdditionalPlacePrice() const
{
  int calculated = roomsCalculatedAdditionalPlacePrice();
  bool hasManual = _manualRoomsAdditionalPlacePrice >= 0;
  return PricePair(calculated, hasManual ? _manualRoomsAdditionalPlacePrice : calculated, hasManual);
}

PricePair Price::parkingPrice() const
{
  int calculated = parkingCalculatedPrice();
  bool hasManual = _manualParkingPrice >= 0;
  return PricePair(calculated, hasManual ? _manualParkingPrice : calculated, hasManual);
}

PricePair Price::fullPrice() const
{
  bool hasManual = _manualRoomsPrice >= 0 || _manualRoomsEmptyPlacePrice >= 0 || _manualRoomsAdditionalPlacePrice >= 0 || _manualParkingPrice >= 0;
  return PricePair(fullCalculatedPrice(), fullManualPrice(), hasManual);
}

void Price::setRoomsPrice(int value)
{
  if (value != roomsCalculatedPrice())
  {
    _manualRoomsPrice = value;
  }
  else
  {
    _manualRoomsPrice = -1;
  }
}

void Price::setRoomsEmptyPlacePrice(int value)
{
  if (value != roomsCalculatedEmptyPlacePrice())
  {
    _manualRoomsEmptyPlacePrice = value;
  }
  else
  {
    _manualRoomsEmptyPlacePrice = -1;
  }
}

void Price::setRoomsAdditionalPlacePrice(int value)
{
  if (value != roomsCalculatedAdditionalPlacePrice())
  {
    _manualRoomsAdditionalPlacePrice = value;
  }
  else
  {
    _manualRoomsAdditionalPlacePrice = -1;
  }
}

void Price::setParkingPrice(int value)
{
  if (value != parkingCalculatedPrice())
  {
    _manualParkingPrice = value;
  }
  else
  {
    _manualParkingPrice = -1;
  }
}

void Price::setFullPrice(int value)
{
  if (value != fullCalculatedPrice())
  {
    _manualFullPrice = value;
  }
  else
  {
    _manualFullPrice = -1;
  }
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
    _roomParticipantsPrices[room] += DatabaseHandler::instance()->roomCost(currentDate) * _rooms[room].first;
    _roomAdditionalParticipantsPrices[room] += DatabaseHandler::instance()->additionalPlaceCost(currentDate) * _rooms[room].second;
    if (_countEmptyPlace)
    {
      addEmptyPlacePrice(currentDate, room);
    }
  }
}

void Price::addEmptyPlacePrice(QDate currentDate, RoomPtr room)
{
  int roomEmptyPlaceCount = room->maxParticipants() - _rooms[room].first;
  if (roomEmptyPlaceCount > 0)
  {
    _roomEmptyPlacePrices[room] += DatabaseHandler::instance()->emptyPlaceCost(currentDate) * roomEmptyPlaceCount;
  }
}

void Price::addParkingPrice(QDate currentDate)
{
  _parkingPrice += DatabaseHandler::instance()->parkingCost(currentDate);
}

int Price::roomsCalculatedPrice() const
{
  if (_roomParticipantsPrices.size() > 0)
  {
    QList<int> values = _roomParticipantsPrices.values();
    return std::accumulate(values.begin(), values.end(), 0);
  }
  else
  {
    return 0;
  }
}

int Price::roomsCalculatedEmptyPlacePrice() const
{
  if (_roomEmptyPlacePrices.size() > 0)
  {
    QList<int> values = _roomEmptyPlacePrices.values();
    return std::accumulate(values.begin(), values.end(), 0);
  }
  else
  {
    return 0;
  }
}

int Price::roomsCalculatedAdditionalPlacePrice() const
{
  if (_roomAdditionalParticipantsPrices.size() > 0)
  {
    QList<int> values = _roomAdditionalParticipantsPrices.values();
    return std::accumulate(values.begin(), values.end(), 0);
  }
  else
  {
    return 0;
  }
}

int Price::parkingCalculatedPrice() const
{
  return _parkingPrice;
}

int Price::fullCalculatedPrice() const
{
  return roomsCalculatedPrice() +
         roomsCalculatedEmptyPlacePrice() +
         roomsCalculatedAdditionalPlacePrice() +
         parkingCalculatedPrice();
}

int Price::fullManualPrice() const
{
  if (_manualFullPrice >= 0)
  {
    return _manualFullPrice;
  }
  else
  {
    int price = 0;
    price += _manualRoomsPrice >= 0 ? _manualRoomsPrice : roomsCalculatedPrice();
    price += _manualRoomsEmptyPlacePrice >= 0 ? _manualRoomsEmptyPlacePrice : roomsCalculatedEmptyPlacePrice();
    price += _manualRoomsAdditionalPlacePrice >= 0 ? _manualRoomsAdditionalPlacePrice : roomsCalculatedAdditionalPlacePrice();
    price += _manualParkingPrice >= 0 ? _manualParkingPrice : parkingCalculatedPrice();
    return price;
  }
}

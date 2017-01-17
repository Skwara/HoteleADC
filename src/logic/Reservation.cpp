#include "Reservation.h"
#include "data/DatabaseHandler.h"


Reservation::Reservation()
  : _client(nullptr)
  , _parking(false)
  , _countEmptyPlace(true)
  , _price(_beginDate, _endDate, _rooms, _parking, _countEmptyPlace)
{
  connect(this, SIGNAL(dateChanged()), this, SLOT(updatePrice()), Qt::DirectConnection);
  connect(this, SIGNAL(roomsChanged()), this, SLOT(updatePrice()), Qt::DirectConnection);
  connect(this, SIGNAL(participantsChanged()), this, SLOT(updatePrice()), Qt::DirectConnection);
  connect(this, SIGNAL(additionalChanged()), this, SLOT(updatePrice()), Qt::DirectConnection);
}

ClientPtr Reservation::client() const
{
  return _client;
}

QList<RoomPtr> Reservation::rooms() const
{
  QList<RoomPtr> keys = _rooms.keys();
  std::sort(keys.begin(), keys.end(), [](const RoomPtr& lhs, const RoomPtr& rhs){ return lhs->number() < rhs->number(); });
  return keys;
}

int Reservation::participantsCount() const
{
  return std::accumulate(_rooms.begin(), _rooms.end(), 0);
}

int Reservation::participantsCountPerRoom(RoomPtr room)
{
  return _rooms[room];
}

int Reservation::emptyPlaceCount() const
{
  QList<RoomPtr> rooms = _rooms.keys();
  int placeCount = std::accumulate(rooms.begin(), rooms.end(), 0, [](int sum, const RoomPtr& room){ return sum + room->maxParticipants(); });
  return placeCount - participantsCount();
}

Price Reservation::price() const
{
  return _price;
}

QDate Reservation::beginDate() const
{
  return _beginDate;
}

QDate Reservation::endDate() const
{
  return _endDate;
}

int Reservation::days() const
{
  return _beginDate.daysTo(_endDate);
}

bool Reservation::parking() const
{
  return _parking;
}

bool Reservation::countEmptyPlace() const
{
  return _countEmptyPlace;
}

void Reservation::setClient(ClientPtr client)
{
  _client = client;
  emit clientChanged();
}

void Reservation::addRoom(RoomPtr room)
{
  _rooms.insert(room, 0);
  emit roomsChanged();
}

void Reservation::removeRoom(RoomPtr room)
{
  _rooms.remove(room);
  emit roomsChanged();
}

void Reservation::setRoomParticipants(RoomPtr room, int participantsCount)
{
  _rooms[room] = participantsCount;
  emit participantsChanged();
}

void Reservation::setBeginDate(const QDate& date)
{
  _beginDate = date;
  emit dateChanged();
}

void Reservation::setEndDate(const QDate& date)
{
  _endDate = date;
  emit dateChanged();
}

void Reservation::setParking(bool value)
{
  _parking = value;
  emit additionalChanged();
}

void Reservation::setCountEmptyPlace(bool value)
{
  _countEmptyPlace = value;
  emit additionalChanged();
}

void Reservation::updatePrice()
{
  _price = Price(_beginDate, _endDate, _rooms, _parking, _countEmptyPlace);
}

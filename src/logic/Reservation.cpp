#include "Reservation.h"
#include "data/DataHandler.h"


Reservation::Reservation()
  : _id(-1)
  , _client(nullptr)
  , _batch(nullptr)
  , _beginDate(QDate::currentDate())
  , _endDate(QDate::currentDate())
  , _parking(false)
  , _countEmptyPlace(true)
  , _price(_beginDate, _endDate, _rooms, _parking, _countEmptyPlace)
{
}

Reservation::Reservation(const Reservation& reservation)
  : _id(reservation._id)
  , _client(reservation._client)
  , _rooms(reservation._rooms)
  , _batch(reservation._batch)
  , _beginDate(reservation._beginDate)
  , _endDate(reservation._endDate)
  , _parking(reservation._parking)
  , _countEmptyPlace(reservation._countEmptyPlace)
  , _price(reservation._price)
{
}

long long Reservation::id() const
{
  return _id;
}

QString Reservation::description(RoomPtr room) const
{
  return QString("Pokój: %1\n" \
                 "Data: %2\n" \
                 "Koszt: %3\n" \
                 "Zaliczka: %4\n" \
                 "Wpłacono: %5")
                 .arg(room->number())
                 .arg(_beginDate.toString("dd-MMM"))
                 .arg(_price.fullPrice().manual())
                 .arg(_price.advance())
                 .arg(_price.paid());
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

int Reservation::mainParticipantsCount() const
{
  return std::accumulate(_rooms.begin(), _rooms.end(), 0,
                         [](int sum, QPair<int, int> val){ return sum + val.first; });
}

int Reservation::mainParticipantsCountPerRoom(RoomPtr room) const
{
  return _rooms[room].first;
}

int Reservation::additionalParticipantsCount() const
{
  return std::accumulate(_rooms.begin(), _rooms.end(), 0,
                         [](int sum, QPair<int, int> val){ return sum + val.second; });
}

int Reservation::additionalParticipantsCountPerRoom(RoomPtr room) const
{
  return _rooms[room].second;
}

int Reservation::emptyPlaceCount() const
{
  QList<RoomPtr> rooms = _rooms.keys();
  int placeCount = std::accumulate(rooms.begin(), rooms.end(), 0, [](int sum, const RoomPtr& room){ return sum + room->maxParticipants(); });
  return placeCount - mainParticipantsCount();
}

bool Reservation::isBatch() const
{
  return _batch != nullptr;
}

BatchPtr Reservation::batch() const
{
  return _batch;
}

Price& Reservation::price()
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

void Reservation::setId(long long id)
{
  _id = id;
}

void Reservation::setClient(ClientPtr client)
{
  _client = client;
  emit clientChanged();
}

void Reservation::addRoom(RoomPtr room)
{
  foreach (RoomPtr keyRoom, _rooms.keys())
    if (keyRoom->id() == room->id())
      return;

  _rooms.insert(room, QPair<int, int>(0, 0));
  updatePrice();
  emit roomsChanged();
}

void Reservation::removeRoom(RoomPtr room)
{
  _rooms.remove(room);
  updatePrice();
  emit roomsChanged();
}

void Reservation::setRoomMainParticipants(RoomPtr room, int mainParticipantsCount)
{
  _rooms[room].first = mainParticipantsCount;
  updatePrice();
  emit participantsChanged();
}

void Reservation::setRoomAdditionalParticipants(RoomPtr room, int additionalParticipantsCount)
{
  _rooms[room].second = additionalParticipantsCount;
  updatePrice();
  emit participantsChanged();
}

void Reservation::setBatch(BatchPtr batch)
{
  _batch = batch;
  setBeginDate(batch->beginDate());
  setEndDate(batch->endDate());
}

void Reservation::setBeginDate(const QDate& date)
{
  _beginDate = date;
  updatePrice();
  emit dateChanged();
}

void Reservation::setEndDate(const QDate& date)
{
  _endDate = date;
  updatePrice();
  emit dateChanged();
}

void Reservation::setParking(bool value)
{
  _parking = value;
  updatePrice();
  emit additionalChanged();
}

void Reservation::setCountEmptyPlace(bool value)
{
  _countEmptyPlace = value;
  updatePrice();
  emit additionalChanged();
}

void Reservation::updatePrice()
{
  _price.update(_beginDate, _endDate, _rooms, _parking, _countEmptyPlace);
}

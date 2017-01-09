#include "Reservation.h"
#include "data/DatabaseHandler.h"


Reservation::Reservation()
  : _client(nullptr)
  , _parking(false)
{
}

ClientPtr Reservation::client() const
{
  return _client;
}

QStringList Reservation::participants() const
{
  return _participants;
}

QList<RoomPtr> Reservation::rooms() const
{
  return _rooms;
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

  // TODO Pricing based on rooms. When adding participants, rooms need to be assigned

  return price;
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

void Reservation::setClient(ClientPtr client)
{
  _client = client;
  emit clientChanged();
}

void Reservation::addParticipant(QString participant)
{
  _participants.append(participant);
  emit participantsChanged();
}

void Reservation::removeParticipant(QString participant)
{
  _participants.removeOne(participant);
  emit participantsChanged();
}

void Reservation::addRoom(RoomPtr room)
{
  _rooms.append(room);
  emit roomsChanged();
}

void Reservation::removeRoom(RoomPtr room)
{
  _rooms.removeOne(room);
  emit roomsChanged();
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

#include "DataHandler.h"


// TODO Connect mock methods to database
DataHandler DataHandler::_instance;

DataHandler::DataHandler()
  : _fetched(false)
{
  // TODO fetching in another thread
  fetch();
}

unsigned int DataHandler::nextClientId()
{
  return _nextClientId++;
}

unsigned int DataHandler::nextRoomId()
{
  return _nextRoomId++;
}

unsigned int DataHandler::nextReservationId()
{
  return _nextReservationId++;
}

QList<ClientPtr> DataHandler::clients() const
{
  return _clients;
}

QList<ClientPtr> DataHandler::clients(QString surname, QString name, QString street)
{
  // TODO Clients search should take all data into account?
  QList<ClientPtr> matchingClients;
  foreach (ClientPtr client, _clients)
  {
    if (client->surname() == surname &&
        (name.isEmpty() || client->name() == name) &&
        (street.isEmpty() || client->address().street() == street))
    {
      matchingClients << client;
    }
  }
  return matchingClients;
}

QDate DataHandler::firstDate() const
{
  return QDate(QDate::currentDate().year(), 4, 30);
}

QDate DataHandler::lastDate() const
{
  return QDate(QDate::currentDate().year(), 10, 31);
}

int DataHandler::roomCost(QDate date) const
{
  if (date.month() >= 5 && date.month() <= 8)
  {
    return 100;
  }
  else
  {
    return 80;
  }
}

int DataHandler::emptyPlaceCost(QDate date) const
{
  return static_cast<int>(roomCost(date) * _emptyPlaceFactor);
}

int DataHandler::additionalPlaceCost(QDate date) const
{
  return static_cast<int>(roomCost(date) * _additionalPlaceFactor);
}

int DataHandler::parkingCost(QDate date) const
{
  if (date.month() >= 5 && date.month() <= 8)
  {
    return 10;
  }
  else
  {
    return 8;
  }
}

QList<RoomPtr> DataHandler::rooms() const
{
  return _rooms;
}

RoomPtr DataHandler::room(int index) const
{
  return _rooms.value(index, nullptr);
}

bool DataHandler::isReservationAvailable(ReservationPtr reservation) const
{
  foreach (ReservationPtr r, _reservations)
  {
    if (r->id() == reservation->id())
      continue;

    if (periodsOverlap(reservation->beginDate(), reservation->endDate(),
                       r->beginDate(), r->endDate()))
    {
      foreach (RoomPtr lRoom, reservation->rooms())
      {
        foreach (RoomPtr rRoom, r->rooms())
        {
          if (lRoom == rRoom)
          {
            return false;
          }
        }
      }
    }
  }

  return true;
}

QList<ReservationPtr> DataHandler::reservations() const
{
  return _reservations;
}

ReservationPtr DataHandler::reservation(const QDate& beginDate, const RoomPtr& room) const
{
  QList<ReservationPtr>::const_iterator it = std::find_if(_reservations.begin(), _reservations.end(), [&](const ReservationPtr& reservation)
  {
    return reservation->beginDate() == beginDate &&
           hasElementWithId(reservation->rooms(), room);
  });

  if (it != _reservations.end())
  {
    return *it;
  }

  return nullptr;
}

bool DataHandler::hasAvailableParkingSpace(const ReservationPtr /*reservation*/) const
{
  return true;
}

QList<BatchPtr> DataHandler::batchPeriods() const
{
  return _batchPeriods;
}

BatchPtr DataHandler::batchPeriod(int index) const
{
  return _batchPeriods.value(index, nullptr);
}

BatchPtr DataHandler::batchPeriod(QDate beginDate, QDate endDate)
{
  foreach (BatchPtr batch, _batchPeriods)
  {
    if (batch->beginDate() == beginDate && batch->endDate() == endDate)
    {
      return batch;
    }
  }

  return nullptr;
}

bool DataHandler::saveReservation(const ReservationPtr reservation)
{
  if (!hasElementWithId(_reservations, reservation))
  {
    if (!saveClient(reservation->client()))
      return false;
    reservation->setId(nextReservationId());
    _reservations.append(reservation);
  }
  else
    return updateReservation(reservation);

  return true;
}

bool DataHandler::saveClient(const ClientPtr client)
{
  if (!hasElementWithId(_clients, client))
  {
    client->setId(nextClientId());
    _clients.push_back(client);
  }

  return true;
}

bool DataHandler::saveRoom(const RoomPtr room)
{
  room->setId(nextRoomId());
  _rooms.push_back(room);
  return true;
}

bool DataHandler::deleteReservation(ReservationPtr reservation)
{
  QList<ReservationPtr>::iterator it = std::remove_if(_reservations.begin(), _reservations.end(),
                                                      [&reservation](const ReservationPtr& r){ return r->id() == reservation->id(); });
  bool erased = it != _reservations.end();
  _reservations.erase(it, _reservations.end());
  return erased;
}

bool DataHandler::updateReservation(ReservationPtr reservation)
{
  ClientPtr client = reservation->client();
  QList<ClientPtr> clients = this->clients(client->surname(), client->name(), client->address().street());
  if (clients.size() == 0)
  {
    client->setId(nextClientId());
    saveClient(client);
  }

  if (deleteReservation(reservation))
    _reservations.append(reservation);
  else
    return false;

  return true;
}

bool DataHandler::periodsOverlap(QDate lBeginDate, QDate lEndDate, QDate rBeginDate, QDate rEndDate) const
{
  int periodsSpan = std::min(lBeginDate, rBeginDate).daysTo(std::max(lEndDate, rEndDate));
  int periodslength = lBeginDate.daysTo(lEndDate) + rBeginDate.daysTo(rEndDate);
  return periodsSpan < periodslength;
}

void DataHandler::fetch()
{
  if (_fetched)
  {
    return;
  }

  fetchClients();
  fetchRooms();
  fetchBatchPeriods();
  fetchOther();
  fetchReservations();

  _fetched = true;
}

void DataHandler::fetchClients()
{
  saveClient(std::make_shared<Client>(
             Client("Kowalski", "Jan",
                    Address("al. Pokoju", "22/10", "31-564", "Kraków", "Polska"),
                    "516212757",
                    "skwara0@gmail.com")));
  saveClient(std::make_shared<Client>(
             Client("Kowalski", "Janusz",
                    Address("ul. Grzegórzecka", "17/34", "31-564", "Kraków", "Polska"),
                    "384758678",
                    "janusz@gmail.com")));
  saveClient(std::make_shared<Client>(
             Client("Kowalski", "Janusz",
                    Address("ul. Mogilska", "1", "31-564", "Kraków", "Polska"),
                    "123456789",
                    "januszMogilska@gmail.com")));
  saveClient(std::make_shared<Client>(
             Client("Nowak", "Andrzej",
                    Address("ul. Daniela Chodowieckiego", "8", "31-564", "Kraków", "Polska"),
                    "584757685",
                    "testemail@gmail.com")));
  saveClient(std::make_shared<Client>(
             Client("Iksiński", "Łukasz",
                    Address("al. Pokoju", "24/15", "31-564", "Kraków", "Polska"),
                    "384758698",
                    "mailmail@gmail.com")));
}

void DataHandler::fetchRooms()
{
  saveRoom(std::make_shared<Room>(Room(1, 3)));
  saveRoom(std::make_shared<Room>(Room(2, 3)));
  saveRoom(std::make_shared<Room>(Room(3, 3)));
  saveRoom(std::make_shared<Room>(Room(4, 3)));
  saveRoom(std::make_shared<Room>(Room(5, 3)));
  saveRoom(std::make_shared<Room>(Room(6, 3)));
  saveRoom(std::make_shared<Room>(Room(7, 3)));
  saveRoom(std::make_shared<Room>(Room(8, 3)));
  saveRoom(std::make_shared<Room>(Room(9, 3)));
  saveRoom(std::make_shared<Room>(Room(10, 3)));

  std::sort(_rooms.begin(), _rooms.end(),
            [](const RoomPtr& lRoom, const RoomPtr& rRoom){ return lRoom->number() < rRoom->number(); });
}

void DataHandler::fetchReservations()
{
  ReservationPtr reservation = std::make_shared<Reservation>();

  reservation->setClient(_clients[0]);
  reservation->addRoom(_rooms[0]);
  reservation->setBeginDate(QDate(QDate::currentDate().year(), 5, 2));
  reservation->setEndDate(QDate(QDate::currentDate().year(), 5, 9));
  reservation->setRoomMainParticipants(_rooms[0], 3);
  saveReservation(reservation);

  reservation = std::make_shared<Reservation>();
  reservation->setClient(_clients[1]);
  reservation->addRoom(_rooms[1]);
  reservation->setBeginDate(QDate(QDate::currentDate().year(), 5, 1));
  reservation->setEndDate(QDate(QDate::currentDate().year(), 5, 7));
  saveReservation(reservation);

  reservation = std::make_shared<Reservation>();
  reservation->setClient(_clients[2]);
  reservation->addRoom(_rooms[3]);
  reservation->setBeginDate(QDate(QDate::currentDate().year(), 5, 1));
  reservation->setEndDate(QDate(QDate::currentDate().year(), 5, 7));
  saveReservation(reservation);

  reservation = std::make_shared<Reservation>();
  reservation->setClient(_clients[3]);
  reservation->addRoom(_rooms[3]);
  reservation->setBeginDate(QDate(QDate::currentDate().year(), 5, 7));
  reservation->setEndDate(QDate(QDate::currentDate().year(), 5, 14));
  saveReservation(reservation);

  reservation = std::make_shared<Reservation>();
  reservation->setClient(_clients[3]);
  reservation->addRoom(_rooms[6]);
  reservation->setBatch(_batchPeriods[1]);
  saveReservation(reservation);
}

void DataHandler::fetchBatchPeriods()
{
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 4, 30), QDate(2017, 5, 14), {"D"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 5, 7), QDate(2017, 5, 21), {"B", "C"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 5, 14), QDate(2017, 5, 28), {"D"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 5, 21), QDate(2017, 6, 4), {"A", "B", "C"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 5, 28), QDate(2017, 6, 11), {"D"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 6, 4), QDate(2017, 6, 18), {"A", "B", "C"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 6, 11), QDate(2017, 6, 25), {"D"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 6, 18), QDate(2017, 7, 2), {"A", "B", "C"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 6, 25), QDate(2017, 7, 9), {"D"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 7, 2), QDate(2017, 7, 16), {"A", "B", "C"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 7, 9), QDate(2017, 7, 23), {"D"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 7, 16), QDate(2017, 7, 30), {"A", "B", "C"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 7, 23), QDate(2017, 8, 6), {"D"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 7, 30), QDate(2017, 8, 13), {"A", "B", "C"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 8, 6), QDate(2017, 8, 20), {"D"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 8, 13), QDate(2017, 8, 27), {"A", "B", "C"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 8, 20), QDate(2017, 9, 3), {"D"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 8, 27), QDate(2017, 9, 10), {"A", "B", "C"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 9, 3), QDate(2017, 9, 17), {"D"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 9, 10), QDate(2017, 9, 24), {"A", "B", "C"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 9, 17), QDate(2017, 10, 1), {"D"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 9, 24), QDate(2017, 10, 8), {"B", "C"})));
  _batchPeriods.push_back(std::make_shared<Batch>(Batch(QDate(2017, 10, 1), QDate(2017, 10, 15), {"D"})));
}

void DataHandler::fetchOther()
{
  _emptyPlaceFactor = 0.6;
  _additionalPlaceFactor = 0.6;
}

template<typename T>
bool DataHandler::hasElementWithId(QList<T> container, T element) const
{
  return std::any_of(container.begin(), container.end(),
                     [&element](const T& e){ return e->id() == element->id(); });
}

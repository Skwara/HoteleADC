#include "DatabaseHandler.h"


DatabaseHandler DatabaseHandler::_instance;

DatabaseHandler::DatabaseHandler()
  : _fetched(false)
{
  // TODO fetching in another thread
  fetch();
}

QList<ClientPtr> DatabaseHandler::clients(QString surname, QString name, QString street)
{
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

QDate DatabaseHandler::firstDate() const
{
  // TODO Mock method for first date
  return QDate(QDate::currentDate().year(), 5, 1);
}

QDate DatabaseHandler::lastDate() const
{
  // TODO Mock method for last date
  return QDate(QDate::currentDate().year(), 10, 31);
}

int DatabaseHandler::roomCost(QDate date) const
{
  // TODO Mock method for room pricing
  if (date.month() >= 5 && date.month() <= 8)
  {
    return 100;
  }
  else
  {
    return 80;
  }
}

int DatabaseHandler::emptyPlaceCost(QDate date) const
{
  return roomCost(date) * _emptyPlaceFactor;
}

int DatabaseHandler::parkingCost(QDate date) const
{
  // TODO Mock method for parking pricing
  if (date.month() >= 5 && date.month() <= 8)
  {
    return 10;
  }
  else
  {
    return 8;
  }
}

ReservationPtr DatabaseHandler::reservation(const QDate& beginDate, const RoomPtr& room) const
{
  QList<ReservationPtr>::const_iterator it = std::find_if(_reservations.begin(), _reservations.end(), [&](const ReservationPtr& reservation)
  {
    return reservation->beginDate() == beginDate &&
           reservation->rooms().contains(room);
  });

  if (it != _reservations.end())
  {
    return *it;
  }

  return nullptr;
}

bool DatabaseHandler::hasAvailableParkingSpace(const Reservation& /*reservation*/) const
{
  return true; // TODO Check with database
}

void DatabaseHandler::fetch()
{
  if (_fetched)
  {
    return;
  }

  fetchClients();
  fetchRooms();
  fetchReservations();
  fetchOther();

  _fetched = true;
}

void DatabaseHandler::fetchClients()
{
  // TODO Mock method for fetching clients
  _clients.push_back(std::make_shared<Client>(
                     Client("Kowalski", "Jan",
                            Address("al. Pokoju", "22/10", "31-564", "Kraków", "Polska"),
                            "516212757",
                            "skwara0@gmail.com")));
  _clients.push_back(std::make_shared<Client>(
                     Client("Kowalski", "Janusz",
                            Address("ul. Grzegórzecka", "17/34", "31-564", "Kraków", "Polska"),
                            "384758678",
                            "janusz@gmail.com")));
  _clients.push_back(std::make_shared<Client>(
                     Client("Kowalski", "Janusz",
                            Address("ul. Mogilska", "1", "31-564", "Kraków", "Polska"),
                            "123456789",
                            "januszMogilska@gmail.com")));
  _clients.push_back(std::make_shared<Client>(
                     Client("Nowak", "Andrzej",
                            Address("ul. Daniela Chodowieckiego", "8", "31-564", "Kraków", "Polska"),
                            "584757685",
                            "testemail@gmail.com")));
  _clients.push_back(std::make_shared<Client>(
                     Client("Iksiński", "Łukasz",
                            Address("al. Pokoju", "24/15", "31-564", "Kraków", "Polska"),
                            "384758698",
                            "mailmail@gmail.com")));
}

void DatabaseHandler::fetchRooms()
{
  // TODO Mock method for fetching rooms
  _rooms.push_back(std::make_shared<Room>(Room(1, 3)));
  _rooms.push_back(std::make_shared<Room>(Room(2, 3)));
  _rooms.push_back(std::make_shared<Room>(Room(3, 3)));
  _rooms.push_back(std::make_shared<Room>(Room(4, 3)));
  _rooms.push_back(std::make_shared<Room>(Room(5, 3)));
  _rooms.push_back(std::make_shared<Room>(Room(6, 3)));
  _rooms.push_back(std::make_shared<Room>(Room(7, 3)));
  _rooms.push_back(std::make_shared<Room>(Room(8, 3)));
  _rooms.push_back(std::make_shared<Room>(Room(9, 3)));
  _rooms.push_back(std::make_shared<Room>(Room(10, 3)));
}

void DatabaseHandler::fetchReservations()
{
  // TODO Mock method for fetching reservations
  ReservationPtr reservation = std::make_shared<Reservation>();

  reservation->setClient(_clients[0]);
  reservation->addRoom(_rooms[0]);
  reservation->setBeginDate(QDate(QDate::currentDate().year(), 5, 2));
  reservation->setEndDate(QDate(QDate::currentDate().year(), 5, 9));
  _reservations.push_back(reservation);

  reservation = std::make_shared<Reservation>();
  reservation->setClient(_clients[1]);
  reservation->addRoom(_rooms[1]);
  reservation->setBeginDate(QDate(QDate::currentDate().year(), 5, 1));
  reservation->setEndDate(QDate(QDate::currentDate().year(), 5, 7));
  _reservations.push_back(reservation);

  reservation = std::make_shared<Reservation>();
  reservation->setClient(_clients[2]);
  reservation->addRoom(_rooms[3]);
  reservation->setBeginDate(QDate(QDate::currentDate().year(), 5, 1));
  reservation->setEndDate(QDate(QDate::currentDate().year(), 5, 7));
  _reservations.push_back(reservation);

  reservation = std::make_shared<Reservation>();
  reservation->setClient(_clients[3]);
  reservation->addRoom(_rooms[3]);
  reservation->setBeginDate(QDate(QDate::currentDate().year(), 5, 7));
  reservation->setEndDate(QDate(QDate::currentDate().year(), 5, 14));
  _reservations.push_back(reservation);
}

void DatabaseHandler::fetchOther()
{
  // TODO Mock method for fetching other
  _emptyPlaceFactor = 0.6f;
}

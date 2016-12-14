#include "DatabaseHandler.h"

DatabaseHandler* DatabaseHandler::_instance = nullptr;

DatabaseHandler::DatabaseHandler()
  : _fetched(false)
{
  // TODO fetching in another thread
  fetch();
}

QList<Client> DatabaseHandler::clients(QString surname, QString name, QString street)
{
  QList<Client> matchingClients;
  foreach (Client client, _clients)
  {
    if (client.surname() == surname &&
        (name.isEmpty() || client.name() == name) &&
        (street.isEmpty() || client.address().street() == street))
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

int DatabaseHandler::dateCost(QDate date) const
{
  // TODO Mock method for pricing
  if (date.month() >= 5 && date.month() <= 8)
  {
    return 100;
  }
  else
  {
    return 80;
  }
}

ReservationPtr DatabaseHandler::reservation(const QDate& beginDate, const Room& room) const
{
  QList<Reservation>::const_iterator it = std::find_if(_reservations.begin(), _reservations.end(), [&](const Reservation& reservation)
  {
    return reservation.beginDate() == beginDate &&
           *reservation.room() == room;
  });

  if (it != _reservations.end())
  {
    return std::make_shared<Reservation>(*it);
  }

  return nullptr;
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

  _fetched = true;
}

void DatabaseHandler::fetchClients()
{
  // TODO Mock method for fetching clients
  _clients.push_back(Client("Kowalski", "Jan",
                            Address("al. Pokoju", "22/10", "31-564", "Kraków", "Polska"),
                            "516212757",
                            "skwara0@gmail.com"));
  _clients.push_back(Client("Kowalski", "Janusz",
                            Address("ul. Grzegórzecka", "17/34", "31-564", "Kraków", "Polska"),
                            "384758678",
                            "janusz@gmail.com"));
  _clients.push_back(Client("Kowalski", "Janusz",
                            Address("ul. Mogilska", "1", "31-564", "Kraków", "Polska"),
                            "123456789",
                            "januszMogilska@gmail.com"));
  _clients.push_back(Client("Nowak", "Andrzej",
                            Address("ul. Daniela Chodowieckiego", "8", "31-564", "Kraków", "Polska"),
                            "584757685",
                            "testemail@gmail.com"));
  _clients.push_back(Client("Iksiński", "Łukasz",
                            Address("al. Pokoju", "24/15", "31-564", "Kraków", "Polska"),
                            "384758698",
                            "mailmail@gmail.com"));
}

void DatabaseHandler::fetchRooms()
{
  // TODO Mock method for fetching rooms
  _rooms.push_back(Room(1));
  _rooms.push_back(Room(2));
  _rooms.push_back(Room(3));
  _rooms.push_back(Room(4));
  _rooms.push_back(Room(5));
  _rooms.push_back(Room(6));
  _rooms.push_back(Room(7));
  _rooms.push_back(Room(8));
  _rooms.push_back(Room(9));
  _rooms.push_back(Room(10));
}

void DatabaseHandler::fetchReservations()
{
  // TODO Mock method for fetching reservations
  Reservation reservation;
  reservation.setClient(_clients[0]);
  reservation.setRoom(_rooms[0]);
  reservation.setBeginDate(QDate(QDate::currentDate().year(), 5, 2));
  reservation.setEndDate(QDate(QDate::currentDate().year(), 5, 9));
  _reservations.push_back(reservation);
}

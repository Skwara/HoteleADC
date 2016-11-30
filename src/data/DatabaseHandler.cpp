#include "DatabaseHandler.h"

QList<Client> DatabaseHandler::_clients = QList<Client>();
bool DatabaseHandler::_fetched = false;

DatabaseHandler::DatabaseHandler()
{
  // TODO fetching in another thread
  fetchClients();
}

QList<Client> DatabaseHandler::clients(QString surname, QString name, QString street)
{
  QList<Client> matchingClients;
  foreach (Client client, DatabaseHandler::_clients)
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

void DatabaseHandler::fetchClients()
{
  if (DatabaseHandler::_fetched)
  {
    return;
  }

  // TODO Mock method for fetching clients
  DatabaseHandler::_clients.push_back(Client("Kowalski", "Jan",
                                             Address("al. Pokoju", "22/10", "31-564", "Kraków", "Polska"),
                                             "516212757",
                                             "skwara0@gmail.com"));
  DatabaseHandler::_clients.push_back(Client("Kowalski", "Janusz",
                                             Address("ul. Grzegórzecka", "17/34", "31-564", "Kraków", "Polska"),
                                             "384758678",
                                             "janusz@gmail.com"));
  DatabaseHandler::_clients.push_back(Client("Kowalski", "Janusz",
                                             Address("ul. Mogilska", "1", "31-564", "Kraków", "Polska"),
                                             "123456789",
                                             "januszMogilska@gmail.com"));
  DatabaseHandler::_clients.push_back(Client("Nowak", "Andrzej",
                                             Address("ul. Daniela Chodowieckiego", "8", "31-564", "Kraków", "Polska"),
                                             "584757685",
                                             "testemail@gmail.com"));
  DatabaseHandler::_clients.push_back(Client("Iksiński", "Łukasz",
                                             Address("al. Pokoju", "24/15", "31-564", "Kraków", "Polska"),
                                             "384758698",
                                             "mailmail@gmail.com"));

  DatabaseHandler::_fetched = true;
}

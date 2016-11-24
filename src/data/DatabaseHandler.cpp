#include "DatabaseHandler.h"

DatabaseHandler::DatabaseHandler()
{
  // TODO fetching in another thread
  fetchClients();
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
  _clients.push_back(Client("Nowak", "Andrzej", Address("ul. Daniela Chodowieckiego", "8", "31-564", "Kraków", "Polska"),
                            "584757685",
                            "testemail@gmail.com"));
  _clients.push_back(Client("Iksiński", "Łukasz", Address("al. Pokoju", "24/15", "31-564", "Kraków", "Polska"),
                            "384758698",
                            "mailmail@gmail.com"));
}

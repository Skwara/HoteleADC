#include "DatabaseHandler.h"

DatabaseHandler::DatabaseHandler()
{
  // TODO fetching in another thread
  fetchClients();
}

void DatabaseHandler::fetchClients()
{
  // TODO Mock method
  _clients.push_back(Client("Kowalski", "Jan",
                            Address("al. Pokoju", "22/10", "31-564", "Kraków", "Polska"),
                            "516212757",
                            "skwara0@gmail.com"));
  _clients.push_back(Client("Nowak", "Andrzej", Address("ul. Daniela Chodowieckiego", "8", "31-564", "Kraków", "Polska"),
                            "584757685",
                            "testemail@gmail.com"));
  _clients.push_back(Client("Iksiński", "Łukasz", Address("al. Pokoju", "22/10", "31-564", "Kraków", "Polska"),
                            "384758698",
                            "mailmail@gmail.com"));
}

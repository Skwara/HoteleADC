#include "DatabaseHandler.h"

DatabaseHandler::DatabaseHandler()
{

}

void DatabaseHandler::fetchClients()
{
  // TODO Mock method
  _clients.push_back(Client("Kowalski", "Jan"));
  _clients.push_back(Client("Nowak", "Andrzej"));
  _clients.push_back(Client("Iksiński", "Łukasz"));
}

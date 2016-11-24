#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QStringList>
#include <QList>

#include "logic/Client.h"

#include <iostream>
class DatabaseHandler
{
public:
  DatabaseHandler();

  QList<Client> clients() const { return _clients; }

private:
  void fetchClients();

private:
  QList<Client> _clients;
};

#endif // DATABASEHANDLER_H

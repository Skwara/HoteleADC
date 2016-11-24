#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QStringList>
#include <QList>

#include "logic/Client.h"

class DatabaseHandler
{
public:
  DatabaseHandler();

  QList<Client> clients() const { return _clients; }
  QList<Client> clients(QString surname, QString name, QString street);

private:
  void fetchClients();

private:
  QList<Client> _clients;
};

#endif // DATABASEHANDLER_H

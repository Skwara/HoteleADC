#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QStringList>
#include <QList>
#include <QDate>

#include "logic/Client.h"

class DatabaseHandler
{
public:
  DatabaseHandler();

  QList<Client> clients() const { return _clients; }
  QList<Client> clients(QString surname, QString name, QString street);

  int dateCost(QDate date) const;

private:
  void fetchClients();

private:
  static QList<Client> _clients;

  static bool _fetched;
};

#endif // DATABASEHANDLER_H

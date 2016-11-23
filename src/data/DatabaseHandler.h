#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QStringList>

#include "logic/Client.h"

class DatabaseHandler
{
public:
  DatabaseHandler();

  QStringList surnames() const;
  QStringList names() const;
};

#endif // DATABASEHANDLER_H

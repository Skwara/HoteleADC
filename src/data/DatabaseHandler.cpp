#include "DatabaseHandler.h"

DatabaseHandler::DatabaseHandler()
{

}

QStringList DatabaseHandler::surnames() const
{
  QStringList surnames;

  // Mock surnames
  // TODO surnames based on name
  surnames << "Kowalski" << "Nowak" << "Iksiński";

  return surnames;
}

QStringList DatabaseHandler::names() const
{
  QStringList names;

  // Mock names
  // TODO names based on surname
  names << "Jan" << "Nowak" << "Łukasz";

  return names;
}

#include "Client.h"

Address::Address(QString street, QString number, QString postalCode, QString city, QString country)
  : _street(street)
  , _number(number)
  , _postalCode(postalCode)
  , _city(city)
  , _country(country)
{
}

void Address::correctStreetFormatting(QString& /*street*/)
{
  // TODO ensure correct street formatting
}

Client::Client(QString surname, QString name, Address address, QString phone, QString eMail)
  : _surname(surname)
  , _name(name)
  , _address(address)
  , _phone(phone)
  , _eMail(eMail)
{
}

void Client::firstLetterUppercase(QString& string)
{
  if (!string.isEmpty())
  {
    string = string.toLower();
    string[0] = string[0].toUpper();
  }
}

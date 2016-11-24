#include "Client.h"

Address::Address(QString street, QString number, QString postalCode, QString city, QString country)
  : street(street)
  , number(number)
  , postalCode(postalCode)
  , city(city)
  , country(country)
{
}

Client::Client(QString surname, QString name, Address address, QString phone, QString eMail)
  : _surname(surname)
  , _name(name)
  , _address(address)
  , _phone(phone)
  , _eMail(eMail)
{
}

#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

struct Address
{
  Address(QString street, QString number, QString postalCode, QString city, QString country);

  QString street;
  QString number;
  QString postalCode;
  QString city;
  QString country;
};

class Client
{
public:
  Client(QString surname, QString name, Address address, QString phone, QString eMail);

  QString surname() const { return _surname; }
  QString name() const { return _name; }
  Address address() const { return _address; }
  QString phone() const { return _phone; }
  QString eMail() const { return _eMail; }

private:
  QString _surname;
  QString _name;
  Address _address;
  QString _phone;
  QString _eMail;
};

#endif // CLIENT_H

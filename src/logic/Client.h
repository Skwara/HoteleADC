#ifndef CLIENT_H
#define CLIENT_H

#include <memory>

#include <QString>

class Address
{
public:
  Address(QString street, QString number, QString postalCode, QString city, QString country);

  QString street() const { return _street; }
  QString number() const { return _number; }
  QString postalCode() const { return _postalCode; }
  QString city() const { return _city; }
  QString country() const { return _country; }

  static void correctStreetFormatting(QString& street);

private:
  QString _street;
  QString _number;
  QString _postalCode;
  QString _city;
  QString _country;
};

class Client
{
public:
  Client(QString surname, QString name, Address address, QString phone, QString eMail);

  long long int id() const { return _id; }
  QString surname() const { return _surname; }
  QString name() const { return _name; }
  Address address() const { return _address; }
  QString phone() const { return _phone; }
  QString eMail() const { return _eMail; }

  void setId(long long int id) { _id = id; }

  static void firstLetterUppercase(QString& string);

private:
  long long int _id;
  QString _surname;
  QString _name;
  Address _address;
  QString _phone;
  QString _eMail;
};

using ClientPtr = std::shared_ptr<Client>;

#endif // CLIENT_H

#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

class Client
{
public:
  Client(QString surname, QString name);

  QString surname() const { return _surname; }
  QString name() const { return _name; }

private:
  QString _surname;
  QString _name;
};

#endif // CLIENT_H

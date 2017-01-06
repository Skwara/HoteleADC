#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QStringList>
#include <QList>
#include <QDate>

#include "logic/Client.h"
#include "logic/Room.h"
#include "logic/Reservation.h"

class DatabaseHandler
{
  DatabaseHandler();
public:

  static DatabaseHandler* instance()
  {
    if (_instance == nullptr)
    {
      _instance = new DatabaseHandler();
    }
    return _instance;
  }

  QList<Client> clients() const { return _clients; }
  QList<Client> clients(QString surname, QString name, QString street);

  QDate firstDate() const;
  QDate lastDate() const;
  int roomCost(QDate date) const;
  int parkingCost(QDate date) const;

  QList<Room> rooms() const { return _rooms; }

  QList<Reservation> reservations() const { return _reservations; }
  ReservationPtr reservation(const QDate& beginDate, const Room& room) const;

  bool hasAvailableParkingSpace(const Reservation& reservation) const;

private:
  void fetch();
  void fetchClients();
  void fetchRooms();
  void fetchReservations();

private:
  QList<Client> _clients;
  QList<Room> _rooms;
  QList<Reservation> _reservations;

  bool _fetched;

private:
  static DatabaseHandler* _instance;
};

#endif // DATABASEHANDLER_H

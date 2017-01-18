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
    return &_instance;
  }

  QList<ClientPtr> clients() const { return _clients; }
  QList<ClientPtr> clients(QString surname, QString name, QString street);

  QDate firstDate() const;
  QDate lastDate() const;
  int roomCost(QDate date) const;
  int emptyPlaceCost(QDate date) const;
  int additionalPlaceCost(QDate date) const;
  int parkingCost(QDate date) const;

  QList<RoomPtr> rooms() const { return _rooms; }
  RoomPtr room(int number) const { return *std::find_if(_rooms.begin(), _rooms.end(),
                                                        [number](const RoomPtr& room){ return room->number() == number; }); }

  QList<ReservationPtr> reservations() const { return _reservations; }
  ReservationPtr reservation(const QDate& beginDate, const RoomPtr& room) const;

  bool hasAvailableParkingSpace(const Reservation& reservation) const;

private:
  void fetch();
  void fetchClients();
  void fetchRooms();
  void fetchReservations();
  void fetchOther();

private:
  QList<ClientPtr> _clients;
  QList<RoomPtr> _rooms;
  QList<ReservationPtr> _reservations;

  float _emptyPlaceFactor;
  float _additionalPlaceFactor;

  bool _fetched;

private:
  static DatabaseHandler _instance;
};

#endif // DATABASEHANDLER_H

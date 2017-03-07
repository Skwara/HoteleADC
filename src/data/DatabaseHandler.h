#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QStringList>
#include <QList>
#include <QDate>

#include "logic/Client.h"
#include "logic/Room.h"
#include "logic/Reservation.h"
#include "logic/Batch.h"


class DatabaseHandler
{
  DatabaseHandler();
public:

  static DatabaseHandler* instance()
  {
    return &_instance;
  }

  unsigned int nextClientId();
  unsigned int nextRoomId();
  unsigned int nextReservationId();

  QList<ClientPtr> clients() const;
  QList<ClientPtr> clients(QString surname, QString name, QString street);

  QDate firstDate() const;
  QDate lastDate() const;
  int roomCost(QDate date) const;
  int emptyPlaceCost(QDate date) const;
  int additionalPlaceCost(QDate date) const;
  int parkingCost(QDate date) const;

  QList<RoomPtr> rooms() const;
  RoomPtr room(int index) const;
  bool isReservationAvailable(ReservationPtr reservation) const;

  QList<ReservationPtr> reservations() const;
  ReservationPtr reservation(const QDate& beginDate, const RoomPtr& room) const;

  bool hasAvailableParkingSpace(const ReservationPtr reservation) const;

  QList<BatchPtr> batchPeriods() const;
  BatchPtr batchPeriod(int index) const;
  BatchPtr batchPeriod(QDate beginDate, QDate endDate);



  bool saveReservation(const ReservationPtr reservation);
  bool saveClient(const ClientPtr client);
  bool saveRoom(const RoomPtr room);



  bool deleteReservation(ReservationPtr reservation);

private:
  bool updateReservation(ReservationPtr reservation);

  bool periodsOverlap(QDate lBeginDate, QDate lEndDate, QDate rBeginDate, QDate rEndDate) const;

  template<typename T>
  bool hasElementWithId(QList<T> container, T element) const;

  void fetch();
  void fetchClients();
  void fetchRooms();
  void fetchReservations();
  void fetchBatchPeriods();
  void fetchOther();

private:
  unsigned int _nextClientId = 0;
  unsigned int _nextRoomId = 0;
  unsigned int _nextReservationId = 0;

  QList<ClientPtr> _clients;
  QList<RoomPtr> _rooms;
  QList<ReservationPtr> _reservations;
  QList<BatchPtr> _batchPeriods;

  double _emptyPlaceFactor;
  double _additionalPlaceFactor;

  bool _fetched;

private:
  static DatabaseHandler _instance;
};

#endif // DATABASEHANDLER_H

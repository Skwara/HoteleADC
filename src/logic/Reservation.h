#ifndef RESERVATION_H
#define RESERVATION_H

#include <QObject>
#include <QDate>
#include <QMap>

#include <memory>

#include "Client.h"
#include "Room.h"
#include "Price.h"


class Reservation : public QObject
{
  Q_OBJECT

public:
  Reservation();

  ClientPtr client() const;
  QList<RoomPtr> rooms() const;
  int participantsCount() const;
  int participantsCountPerRoom(RoomPtr room);
  int emptyPlaceCount() const;
  Price price() const;
  QDate beginDate() const;
  QDate endDate() const;
  int days() const;
  bool parking() const;
  bool countEmptyPlace() const;

  void setClient(ClientPtr client);
  void addRoom(RoomPtr room);
  void removeRoom(RoomPtr room);
  void setRoomParticipants(RoomPtr room, int participantsCount);
  void setBeginDate(const QDate& date);
  void setEndDate(const QDate& date);
  void setParking(bool value);
  void setCountEmptyPlace(bool value);

signals:
  void clientChanged();
  void roomsChanged();
  void participantsChanged();
  void dateChanged();
  void additionalChanged();

private slots:
  void updatePrice();

private:
  ClientPtr _client;
  QMap<RoomPtr, int> _rooms;

  QDate _beginDate;
  QDate _endDate;

  bool _parking;
  bool _countEmptyPlace;

  Price _price;
};

using ReservationPtr = std::shared_ptr<Reservation>;

#endif // RESERVATION_H

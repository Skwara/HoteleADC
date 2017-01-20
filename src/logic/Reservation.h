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
  int mainParticipantsCount() const;
  int mainParticipantsCountPerRoom(RoomPtr room) const;
  int additionalParticipantsCount() const;
  int additionalParticipantsCountPerRoom(RoomPtr room) const;
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
  void setRoomMainParticipants(RoomPtr room, int mainParticipantsCount);
  void setRoomAdditionalParticipants(RoomPtr room, int additionalParticipantsCount);
  void setBeginDate(const QDate& date);
  void setEndDate(const QDate& date);
  void setParking(bool value);
  void setCountEmptyPlace(bool value);

  void setRoomsPrice(int value);
  void setRoomsEmptyPlacePrice(int value);
  void setRoomsAdditionalPlacePrice(int value);
  void setParkingPrice(int value);
  void setFullPrice(int value);

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
  QMap<RoomPtr, QPair<int, int>> _rooms; // QPair<participants, additional>

  QDate _beginDate;
  QDate _endDate;

  bool _parking;
  bool _countEmptyPlace;

  Price _price;
};

using ReservationPtr = std::shared_ptr<Reservation>;

#endif // RESERVATION_H

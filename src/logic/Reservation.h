#ifndef RESERVATION_H
#define RESERVATION_H

#include <QObject>
#include <QDate>
#include <QMap>

#include <memory>

#include "Client.h"
#include "Room.h"
#include "Price.h"
#include "Batch.h"


class Reservation : public QObject
{
  Q_OBJECT

public:
  Reservation();
  Reservation(const Reservation& reservation);

  long long int id() const;
  QString description(RoomPtr room) const;
  ClientPtr client() const;
  QList<RoomPtr> rooms() const;
  int mainParticipantsCount() const;
  int mainParticipantsCountPerRoom(RoomPtr room) const;
  int additionalParticipantsCount() const;
  int additionalParticipantsCountPerRoom(RoomPtr room) const;
  int emptyPlaceCount() const;
  bool isBatch() const;
  BatchPtr batch() const;
  Price& price();
  QDate beginDate() const;
  QDate endDate() const;
  int days() const;
  bool parking() const;
  bool countEmptyPlace() const;

  void setId(long long int id);
  void setClient(ClientPtr client);
  void addRoom(RoomPtr room);
  void removeRoom(RoomPtr room);
  void setRoomMainParticipants(RoomPtr room, int mainParticipantsCount);
  void setRoomAdditionalParticipants(RoomPtr room, int additionalParticipantsCount);
  void setBatch(BatchPtr batch);
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
  long long int _id;

  ClientPtr _client;
  QMap<RoomPtr, QPair<int, int>> _rooms; // QPair<participants, additional>
  BatchPtr _batch;

  QDate _beginDate;
  QDate _endDate;

  bool _parking;
  bool _countEmptyPlace;

  Price _price;
};

using ReservationPtr = std::shared_ptr<Reservation>;

#endif // RESERVATION_H

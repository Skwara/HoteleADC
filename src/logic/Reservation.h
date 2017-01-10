#ifndef RESERVATION_H
#define RESERVATION_H

#include <QObject>
#include <QDate>
#include <QStringList>

#include <memory>

#include "Client.h"
#include "Room.h"

class Reservation : public QObject
{
  Q_OBJECT

public:
  Reservation();

  ClientPtr client() const;
  QList<RoomPtr> rooms() const;
  int participantsCount() const;
  int price() const;
  QDate beginDate() const;
  QDate endDate() const;
  int days() const;
  bool parking() const;

  void setClient(ClientPtr client);
  void addRoom(RoomPtr room);
  void removeRoom(RoomPtr room);
  void setParticipantsCount(int count);
  void setBeginDate(const QDate& date);
  void setEndDate(const QDate& date);
  void setParking(bool value);

signals:
  void clientChanged();
  void roomsChanged();
  void participantsChanged();
  void dateChanged();
  void additionalChanged();

private:
  ClientPtr _client;
  QList<RoomPtr> _rooms;
  int _participantsCount;

  QDate _beginDate;
  QDate _endDate;

  bool _parking;
};

using ReservationPtr = std::shared_ptr<Reservation>;

#endif // RESERVATION_H

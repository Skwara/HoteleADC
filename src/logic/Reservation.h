#ifndef RESERVATION_H
#define RESERVATION_H

#include <QDate>
#include <QStringList>

#include <memory>

#include "Client.h"
#include "Room.h"

class Reservation
{
public:
  Reservation();

  ClientPtr client() const { return _client; }
  QStringList participants() const { return _participants; }
  RoomPtr room() const { return _room; }

  int price() const;

  QDate beginDate() const { return _beginDate; }
  QDate endDate() const { return _endDate; }
  int days() const { return _beginDate.daysTo(_endDate); }

  bool parking() const { return _parking; }



  void setClient(const Client& client) { _client = std::make_shared<Client>(client); }
  void addParticipant(QString participant) { _participants.append(participant); }
  void removeParticipant(QString participant) { _participants.removeOne(participant); }
  void setRoom(const Room& room) { _room = std::make_shared<Room>(room); }

  void setBeginDate(const QDate& date) { _beginDate = date; }
  void setEndDate(const QDate& date) { _endDate = date; }

  void setParking(bool value) { _parking = value; }

private:
  ClientPtr _client;
  QStringList _participants;
  RoomPtr _room;

  QDate _beginDate;
  QDate _endDate;

  bool _parking;
};

using ReservationPtr = std::shared_ptr<Reservation>;

#endif // RESERVATION_H

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
  QStringList participants() const;
  QList<RoomPtr> rooms() const;
  int price() const;
  QDate beginDate() const;
  QDate endDate() const;
  int days() const;
  bool parking() const;

  void setClient(ClientPtr client);
  void addParticipant(QString participant);
  void removeParticipant(QString participant);
  void addRoom(RoomPtr room);
  void removeRoom(RoomPtr room);
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
  QStringList _participants;
  QList<RoomPtr> _rooms;

  QDate _beginDate;
  QDate _endDate;

  bool _parking;
};

using ReservationPtr = std::shared_ptr<Reservation>;

#endif // RESERVATION_H

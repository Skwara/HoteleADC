#ifndef RESERVATION_H
#define RESERVATION_H

#include <QDate>
#include <QStringList>

#include "Client.h"

class Reservation
{
public:
  Reservation();

  ClientPtr client() const { return _client; }
  QStringList participants() const { return _participants; }

  int price() const;

  QDate beginDate() const { return _beginDate; }
  QDate endDate() const { return _endDate; }
  int days() const { return _beginDate.daysTo(_endDate); }


  void setClient(const Client& client) { _client = std::make_unique<Client>(client); }
  void addParticipant(QString participant) { _participants.append(participant); }
  void removeParticipant(QString participant) { _participants.removeOne(participant); }

  void setBeginDate(const QDate& date) { _beginDate = date; }
  void setEndDate(const QDate& date) { _endDate = date; }

private:
  ClientPtr _client;
  QStringList _participants;

  QDate _beginDate;
  QDate _endDate;
};

#endif // RESERVATION_H

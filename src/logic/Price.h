#ifndef PRICE_H
#define PRICE_H

#include "Room.h"

#include <QDate>
#include <QMap>


class Price
{
public:
  Price(QDate beginDate, QDate endDate, QMap<RoomPtr, QPair<int, int>> rooms, bool parking, bool countEmptyPlace);

  int roomPrice(RoomPtr room) const { return _roomParticipantsPrices[room]; }
  int roomsPrice() const;
  int roomEmptyPlacePrice(RoomPtr room) const { return _roomEmptyPlacePrices[room]; }
  int roomsEmptyPlacePrice() const;
  int roomAdditionalPlacePrice(RoomPtr room) const { return _roomAdditionalParticipantsPrices[room]; }
  int roomsAdditionalPlacePrice() const;
  int parkingPrice() const { return _parkingPrice; }
  int fullPrice() const;

private:
  void calculatePrice();
  void addRoomsPrice(QDate currentDate);
  void addEmptyPlacePrice(QDate currentDate, RoomPtr room);
  void addParkingPrice(QDate currentDate);

private:
  QMap<RoomPtr, int> _roomParticipantsPrices;
  QMap<RoomPtr, int> _roomEmptyPlacePrices;
  QMap<RoomPtr, int> _roomAdditionalParticipantsPrices;
  int _parkingPrice;

private:
  QDate _beginDate;
  QDate _endDate;
  QMap<RoomPtr, QPair<int, int>> _rooms;
  bool _parking;
  bool _countEmptyPlace;
};

#endif // PRICE_H

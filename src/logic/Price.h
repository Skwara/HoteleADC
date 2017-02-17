#ifndef PRICE_H
#define PRICE_H

#include "Room.h"

#include <QDate>
#include <QMap>


class PricePair
{
public:
  PricePair(int calculated, int manual, bool hasManual) : _calculated(calculated), _manual(manual), _hasManual(hasManual) {}
  int calculated() const { return _calculated; }
  int manual() const { return _manual; }
  bool hasManual() const { return _hasManual; }
private:
  int _calculated;
  int _manual;
  bool _hasManual;
};

class Price
{
public:
  Price(QDate beginDate, QDate endDate, QMap<RoomPtr, QPair<int, int>> rooms, bool parking, bool countEmptyPlace);

  void update(QDate beginDate, QDate endDate, QMap<RoomPtr, QPair<int, int>> rooms, bool parking, bool countEmptyPlace);

  int roomPrice(RoomPtr room) const { return _roomParticipantsPrices[room]; }
  int roomEmptyPlacePrice(RoomPtr room) const { return _roomEmptyPlacePrices[room]; }
  int roomAdditionalPlacePrice(RoomPtr room) const { return _roomAdditionalParticipantsPrices[room]; }

  PricePair roomsPrice() const;
  PricePair roomsEmptyPlacePrice() const;
  PricePair roomsAdditionalPlacePrice() const;
  PricePair parkingPrice() const;
  PricePair fullPrice() const;

  void setRoomsPrice(int value);
  void setRoomsEmptyPlacePrice(int value);
  void setRoomsAdditionalPlacePrice(int value);
  void setParkingPrice(int value);
  void setFullPrice(int value);

  double discount() const { return _discount; }
  void setDiscount(double value);

private:
  void calculatePrice();
  void addRoomsPrice(QDate currentDate);
  void addEmptyPlacePrice(QDate currentDate, RoomPtr room);
  void addParkingPrice(QDate currentDate);

  int roomsCalculatedPrice() const;
  int roomsCalculatedEmptyPlacePrice() const;
  int roomsCalculatedAdditionalPlacePrice() const;
  int parkingCalculatedPrice() const;
  int fullCalculatedPrice() const;
  int fullManualPrice() const;

private:
  QMap<RoomPtr, int> _roomParticipantsPrices;
  QMap<RoomPtr, int> _roomEmptyPlacePrices;
  QMap<RoomPtr, int> _roomAdditionalParticipantsPrices;
  int _parkingPrice;

  int _manualRoomsPrice = -1;
  int _manualRoomsEmptyPlacePrice = -1;
  int _manualRoomsAdditionalPlacePrice = -1;
  int _manualParkingPrice = -1;
  int _manualFullPrice = -1;

  double _discount;

private:
  QDate _beginDate;
  QDate _endDate;
  QMap<RoomPtr, QPair<int, int>> _rooms;
  bool _parking;
  bool _countEmptyPlace;
};

#endif // PRICE_H

#ifndef ROOM_H
#define ROOM_H

#include <memory>


class Room
{
public:
  Room(int number, int maxParticipants);

  long long int id() const { return _id; }
  int number() const { return _number; }
  int maxParticipants() const { return _maxParticipants; }

  void setId(long long int id) { _id = id; }

  bool operator==(const Room& other) { return this->_number == other._number; }

private:
  long long int _id;
  int _number;
  int _maxParticipants;

};

using RoomPtr = std::shared_ptr<Room>;

#endif // ROOM_H

#ifndef ROOM_H
#define ROOM_H

#include <memory>


class Room
{
public:
  Room(int number, int maxParticipants);

  unsigned int id() const;
  int number() const { return _number; }
  int maxParticipants() const { return _maxParticipants; }

  bool operator==(const Room& other) { return this->_number == other._number; }

private:
  unsigned int _id;
  int _number;
  int _maxParticipants;

};

using RoomPtr = std::shared_ptr<Room>;

#endif // ROOM_H

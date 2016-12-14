#ifndef ROOM_H
#define ROOM_H

#include <memory>


class Room
{
public:
  Room(int number);

  int number() const { return _number; }

  bool operator==(const Room& other) { return this->_number == other._number; }

private:
  int _number;

};

using RoomPtr = std::shared_ptr<Room>;

#endif // ROOM_H

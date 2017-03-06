#include "Room.h"
#include "data/DatabaseHandler.h"

Room::Room(int number, int maxParticipants)
  : _id(DatabaseHandler::instance()->nextRoomId())
  , _number(number)
  , _maxParticipants(maxParticipants)
{
}

unsigned int Room::id() const
{
  return _id;
}

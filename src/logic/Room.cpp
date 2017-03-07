#include "Room.h"
#include "data/DatabaseHandler.h"

Room::Room(int number, int maxParticipants)
  : _id(-1)
  , _number(number)
  , _maxParticipants(maxParticipants)
{
}

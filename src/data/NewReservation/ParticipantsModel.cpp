#include "ParticipantsModel.h"

ParticipantsModel::ParticipantsModel(ReservationPtr reservation)
  : _spinBoxDelegate(reservation, this)
  , _reservation(reservation)
{
}

ParticipantsSpinBoxDelegate& ParticipantsModel::delegate()
{
  return _spinBoxDelegate;
}

int ParticipantsModel::rowCount(const QModelIndex& /*parent*/) const
{
  return _reservation->rooms().size();
}

int ParticipantsModel::columnCount(const QModelIndex& /*parent*/) const
{
  return 3;
}

QVariant ParticipantsModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  if (role == Qt::DisplayRole || role == Qt::EditRole)
  {
    RoomPtr room = _reservation->rooms()[index.row()];
    if (index.column() == 0)
    {
      return room->number();
    }
    else if (index.column() == 1)
    {
      return _reservation->mainParticipantsCountPerRoom(room);
    }
    else if (index.column() == 2)
    {
      return _reservation->additionalParticipantsCountPerRoom(room);
    }
  }

  return QVariant();
}

QVariant ParticipantsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal)
  {
    if (role == Qt::DisplayRole)
    {
      if (section == 0)
      {
        return "Pokój";
      }
      else if (section == 1)
      {
        return "Osoby";
      }
      else if (section == 2)
      {
        return "Dostawki";
      }
    }
  }

  return QVariant();
}

bool ParticipantsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  if (index.isValid() && role == Qt::EditRole)
  {
    if (index.column() == 1)
    {
      _reservation->setRoomMainParticipants(_reservation->rooms()[index.row()], value.toInt());
      return true;
    }
    else if (index.column() == 2)
    {
      _reservation->setRoomAdditionalParticipants(_reservation->rooms()[index.row()], value.toInt());
      return true;
    }
  }

  return false;
}

Qt::ItemFlags ParticipantsModel::flags(const QModelIndex& index) const
{
  if (!index.isValid())
  {
    return Qt::ItemIsEnabled;
  }

  if (index.column() == 1 || index.column() == 2)
  {
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  }

  return QAbstractItemModel::flags(index);
}

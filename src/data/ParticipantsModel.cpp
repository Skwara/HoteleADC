#include "ParticipantsModel.h"

ParticipantsModel::ParticipantsModel(Reservation& reservation)
  : _spinBoxDelegate(reservation, this)
  , _reservation(reservation)
{
}

SpinBoxDelegate& ParticipantsModel::delegate()
{
  return _spinBoxDelegate;
}

int ParticipantsModel::rowCount(const QModelIndex& /*parent*/) const
{
  return _reservation.rooms().size();
}

int ParticipantsModel::columnCount(const QModelIndex& /*parent*/) const
{
  return 2;
}

QVariant ParticipantsModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  if (role == Qt::DisplayRole || role == Qt::EditRole)
  {
    RoomPtr room = _reservation.rooms()[index.row()];
    if (index.column() == 0)
    {
      return room->number();
    }
    else if (index.column() == 1)
    {
      return _reservation.participantsCountPerRoom(room);
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
    }
  }

  return QVariant();
}

Qt::ItemFlags ParticipantsModel::flags(const QModelIndex& index) const
{
  if (!index.isValid())
  {
    return Qt::ItemIsEnabled;
  }

  if (index.column() == 1)
  {
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  }

  return QAbstractItemModel::flags(index);
}

bool ParticipantsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  if (index.isValid() && role == Qt::EditRole)
  {
    _reservation.setRoomParticipants(_reservation.rooms()[index.row()], value.toInt());
    emit dataChanged(this->index(0, 1), this->index(this->rowCount() - 1, 1));
    return true;
  }

  return false;
}

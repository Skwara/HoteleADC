#include "ParticipantsModel.h"

ParticipantsModel::ParticipantsModel(Reservation& reservation)
  : _reservation(reservation)
{
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

  if (role == Qt::DisplayRole)
  {
    if (index.column() == 0)
    {
      return _reservation.rooms()[index.row()]->number();
    }
    else if (index.column() == 1)
    {
      return "P";
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

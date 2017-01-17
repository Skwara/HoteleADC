#include "SummaryModel.h"


SummaryModel::SummaryModel(Reservation& reservation)
  : _reservation(reservation)
{
}

int SummaryModel::rowCount(const QModelIndex& /*parent*/) const
{
  return _rowCount;
}

int SummaryModel::columnCount(const QModelIndex& /*parent*/) const
{
  return 2;
}

QVariant SummaryModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  if (role == Qt::DisplayRole)
  {
    if (index.column() == 0)
    {
      return rowName(index.row());
    }
    else if (index.column() == 1)
    {
      return rowValue(index.row());
    }
  }

  return QVariant();
}

QVariant SummaryModel::rowValue(int row) const
{
  switch (row)
  {
  case 0:
    return _reservation.days();
    break;
  case 1:
    return _reservation.rooms().size();
    break;
  case 2:
    return _reservation.participantsCount();
    break;
  case 3:
    return _reservation.emptyPlaceCount();
    break;
  case 4:
    return _reservation.price().roomsPrice();
    break;
  case 5:
    return _reservation.price().roomsEmptyPlacePrice();
    break;
  case 6:
    return _reservation.price().parkingPrice();
    break;
  case 7:
    return _reservation.price().fullPrice();
    break;
  default:
    break;
  }

  return QVariant();
}

#include "SummaryModel.h"


// TODO Refactoring with Price class
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
  else if (role == Qt::EditRole)
  {
    if (index.column() == 1 && isCostRow(index.row()))
    {
      return QVariant(QString("%1").arg(rowEditValue(index.row()).toInt()));
    }
  }

  return QVariant();
}

bool SummaryModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  bool isNumber = false;
  value.toInt(&isNumber);
  if (index.isValid() && role == Qt::EditRole && (isNumber || value.toString().isEmpty()))
  {
    if (index.column() == 1 && isCostRow(index.row()))
    {
      switch (index.row())
      {
      case 5:
        _reservation.setRoomsPrice(!value.toString().isEmpty() ? value.toInt() : _reservation.price().roomsPrice().calculated());
        break;
      case 6:
        _reservation.setRoomsEmptyPlacePrice(!value.toString().isEmpty() ? value.toInt() : _reservation.price().roomsEmptyPlacePrice().calculated());
        break;
      case 7:
        _reservation.setRoomsAdditionalPlacePrice(!value.toString().isEmpty() ? value.toInt() : _reservation.price().roomsAdditionalPlacePrice().calculated());
        break;
      case 8:
        _reservation.setParkingPrice(!value.toString().isEmpty() ? value.toInt() : _reservation.price().parkingPrice().calculated());
        break;
      case 9:
        _reservation.setFullPrice(!value.toString().isEmpty() ? value.toInt() : _reservation.price().fullPrice().calculated());
        break;
      default:
        return false;
        break;
      }
      return true;
    }
  }

  return false;
}

Qt::ItemFlags SummaryModel::flags(const QModelIndex& index) const
{
  if (!index.isValid())
  {
    return Qt::ItemIsEnabled;
  }

  if (index.column() == 1 && isCostRow(index.row()))
  {
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  }

  return QAbstractItemModel::flags(index);
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
    return _reservation.mainParticipantsCount();
    break;
  case 3:
    return _reservation.emptyPlaceCount();
    break;
  case 4:
    return _reservation.additionalParticipantsCount();
    break;
  case 5:
    return formatPrice(_reservation.price().roomsPrice());
    break;
  case 6:
    return formatPrice(_reservation.price().roomsEmptyPlacePrice());
    break;
  case 7:
    return formatPrice(_reservation.price().roomsAdditionalPlacePrice());
    break;
  case 8:
    return formatPrice(_reservation.price().parkingPrice());
    break;
  case 9:
    return formatPrice(_reservation.price().fullPrice());
    break;
  default:
    break;
  }

  return QVariant();
}

QVariant SummaryModel::rowEditValue(int row) const
{
  switch (row)
  {
  case 5:
    return _reservation.price().roomsPrice().manual();
    break;
  case 6:
    return _reservation.price().roomsEmptyPlacePrice().manual();
    break;
  case 7:
    return _reservation.price().roomsAdditionalPlacePrice().manual();
    break;
  case 8:
    return _reservation.price().parkingPrice().manual();
    break;
  case 9:
    return _reservation.price().fullPrice().manual();
    break;
  default:
    return QVariant();
    break;
  }
}

QVariant SummaryModel::formatPrice(PricePair price) const
{
  // TODO If fullManualPrice is calculated on manual prices, but is same as calculated, then it's not showed
  if (price.hasManual())
  {
    return QVariant(QString("%1 (%2)").arg(price.manual()).arg(price.calculated()));
  }
  else
  {
    return QVariant(QString("%1").arg(price.calculated()));
  }
}

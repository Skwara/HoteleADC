#include "SummaryModel.h"


// TODO Refactoring with Price class
SummaryModel::SummaryModel(ReservationPtr reservation)
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
    if (index.column() == 1 && isRowEditable(index.row()))
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
    if (index.column() == 1 && isRowEditable(index.row()))
    {
      switch (index.row())
      {
      case 5:
        _reservation->setRoomsPrice(!value.toString().isEmpty() ? value.toInt() : _reservation->price().roomsPrice().calculated());
        break;
      case 6:
        _reservation->setRoomsEmptyPlacePrice(!value.toString().isEmpty() ? value.toInt() : _reservation->price().roomsEmptyPlacePrice().calculated());
        break;
      case 7:
        _reservation->setRoomsAdditionalPlacePrice(!value.toString().isEmpty() ? value.toInt() : _reservation->price().roomsAdditionalPlacePrice().calculated());
        break;
      case 8:
        _reservation->setParkingPrice(!value.toString().isEmpty() ? value.toInt() : _reservation->price().parkingPrice().calculated());
        break;
      case 9:
        _reservation->setFullPrice(!value.toString().isEmpty() ? value.toInt() : _reservation->price().fullPrice().calculated());
        break;
      case 10:
        _reservation->setDiscount(!value.toString().isEmpty() ? value.toDouble() / 100 : 0);
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

  if (index.column() == 1 && isRowEditable(index.row()))
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
    return _reservation->days();
  case 1:
    return _reservation->rooms().size();
  case 2:
    return _reservation->mainParticipantsCount();
  case 3:
    return _reservation->emptyPlaceCount();
  case 4:
    return _reservation->additionalParticipantsCount();
  case 5:
    return formatPrice(_reservation->price().roomsPrice());
  case 6:
    return formatPrice(_reservation->price().roomsEmptyPlacePrice());
  case 7:
    return formatPrice(_reservation->price().roomsAdditionalPlacePrice());
  case 8:
    return formatPrice(_reservation->price().parkingPrice());
  case 9:
    return formatPrice(_reservation->price().fullPrice());
  case 10:
    return formatDiscount(_reservation->price().discount());
  default:
    return QVariant();
  }
}

QVariant SummaryModel::rowEditValue(int row) const
{
  switch (row)
  {
  case 5:
    return _reservation->price().roomsPrice().manual();
  case 6:
    return _reservation->price().roomsEmptyPlacePrice().manual();
  case 7:
    return _reservation->price().roomsAdditionalPlacePrice().manual();
  case 8:
    return _reservation->price().parkingPrice().manual();
  case 9:
    return _reservation->price().fullPrice().manual();
  case 10:
    return _reservation->price().discount() * 100;
  default:
    return QVariant();
  }
}

QVariant SummaryModel::formatPrice(PricePair price) const
{
  if (price.hasManual())
  {
    return QVariant(QString("%1 (%2)").arg(price.manual()).arg(price.calculated()));
  }
  else
  {
    return QVariant(QString("%1").arg(price.calculated()));
  }
}

QVariant SummaryModel::formatDiscount(double discount) const
{
  return QVariant(QString("%1 %").arg(discount * 100));
}

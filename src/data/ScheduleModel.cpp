#include "src/data/ScheduleModel.h"

#include <QSize>
#include <QColor>


ScheduleModel* ScheduleModel::_instance = nullptr;

ScheduleModel::ScheduleModel()
  : _dbhandler(DatabaseHandler::instance())
{

}

int ScheduleModel::rowCount(const QModelIndex& /*parent*/) const
{
  return _dbhandler->rooms().size();
}

int ScheduleModel::columnCount(const QModelIndex& /*parent*/) const
{
  return _dbhandler->firstDate().daysTo(_dbhandler->lastDate());
}

QVariant ScheduleModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  ReservationPtr reservation = findReservation(index);
  if (reservation)
  {
    if (role == Qt::DisplayRole)
    {
      return reservation->client()->surname() + " " + reservation->client()->name();
    }
    if (role == Qt::BackgroundRole)
    {
      return QColor(144, 238, 144);
    }
  }

  return QVariant();
}

QVariant ScheduleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal)
  {
    if (role == Qt::DisplayRole)
    {
      return QString("%1").arg(_dbhandler->firstDate().addDays(section).toString("dd\nMMM"));
    }
  }
  else
  {
    if (role == Qt::DisplayRole)
    {
      return QString("%1").arg(section + 1);
    }
  }

  return QVariant();
}

QSize ScheduleModel::span(const QModelIndex& index) const
{
  ReservationPtr reservation = findReservation(index);
  if (reservation)
  {
    return QSize(reservation->days(), 1);
  }

  return QAbstractItemModel::span(index);
}

ReservationPtr ScheduleModel::findReservation(const QModelIndex& index) const
{
  // TODO Caching reservations
  QDate beginDate = _dbhandler->firstDate().addDays(index.column());
  RoomPtr room = _dbhandler->rooms()[index.row()];
  return _dbhandler->reservation(beginDate, room);
}

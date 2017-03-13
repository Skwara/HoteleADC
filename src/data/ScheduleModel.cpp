#include "ScheduleModel.h"

#include <QSize>
#include <QColor>


ScheduleModel ScheduleModel::_instance;

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
  return static_cast<int>(_dbhandler->firstDate().daysTo(_dbhandler->lastDate()));
}

QVariant ScheduleModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  ReservationPtr reservation = getReservation(index);
  if (reservation)
  {
    if (role == Qt::DisplayRole)
    {
      return reservation->client()->surname() + " " + reservation->client()->name();
    }
    if (role == Qt::BackgroundRole)
    {
      if (reservation->isBatch())
      {
        return QColor(144, 144, 238);
      }
      return QColor(144, 238, 144);
    }
    if (role == Qt::ToolTipRole)
    {
      return reservation->description();
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
      return sourceDate(section).toString("dd\nMMM");
    }
  }
  else
  {
    if (role == Qt::DisplayRole)
    {
      return sourceRoom(section)->number();
    }
  }

  return QVariant();
}

QSize ScheduleModel::span(const QModelIndex& index) const
{
  ReservationPtr reservation = getReservation(index);
  if (reservation)
  {
    return QSize(reservation->days(), 1);
  }

  return QAbstractItemModel::span(index);
}

QDate ScheduleModel::sourceDate(int col) const
{
  return _dbhandler->firstDate().addDays(col);
}

RoomPtr ScheduleModel::sourceRoom(int row) const
{
  return _dbhandler->room(row);
}

bool ScheduleModel::deleteReservation(const QModelIndex& index) const
{
  return _dbhandler->deleteReservation(getReservation(index));
}

ReservationPtr ScheduleModel::getReservation(const QModelIndex& index) const
{
  // TODO Caching reservations
  QDate beginDate = sourceDate(index.column());
  RoomPtr room = sourceRoom(index.row());
  return _dbhandler->reservation(beginDate, room);
}

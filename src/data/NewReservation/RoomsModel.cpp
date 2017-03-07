#include "RoomsModel.h"


RoomsModel::RoomsModel()
  : _scheduleModel(ScheduleModel::instance())
{
}

int RoomsModel::rowCount(const QModelIndex& parent) const
{
  return _scheduleModel->rowCount(parent);
}

QVariant RoomsModel::data(const QModelIndex& index, int role) const
{
  return _scheduleModel->headerData(index.row(), Qt::Vertical, role);
}

RoomPtr RoomsModel::sourceRoom(int row) const
{
  return _scheduleModel->sourceRoom(row);
}

int RoomsModel::roomRow(RoomPtr room) const
{
  for (int row = 0; row < rowCount(); ++row)
    if (room->id() == sourceRoom(row)->id())
      return row;

  return -1;
}

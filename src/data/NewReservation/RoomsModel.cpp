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

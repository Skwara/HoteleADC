#ifndef ROOMSMODEL_H
#define ROOMSMODEL_H

#include <QAbstractListModel>

#include "data/ScheduleModel.h"


class RoomsModel : public QAbstractListModel
{
public:
  RoomsModel();

  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role) const;

  RoomPtr sourceRoom(int row) const;
  int roomRow(RoomPtr room) const;

private:
  ScheduleModel* _scheduleModel;
};

#endif // ROOMSMODEL_H

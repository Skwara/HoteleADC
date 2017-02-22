#ifndef ROOMSMODEL_H
#define ROOMSMODEL_H

#include <QAbstractListModel>

#include "data/ScheduleModel.h"


class RoomsModel : public QAbstractListModel
{
public:
  RoomsModel();

  int rowCount(const QModelIndex& parent) const;
  QVariant data(const QModelIndex& index, int role) const;

private:
  ScheduleModel* _scheduleModel;
};

#endif // ROOMSMODEL_H

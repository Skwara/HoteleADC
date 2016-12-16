#ifndef ROOMSMODEL_H
#define ROOMSMODEL_H

#include <QAbstractListModel>

#include "ScheduleModel.h"


class RoomsModel : public QAbstractListModel
{
  RoomsModel();
public:
  static RoomsModel* instance()
  {
    if (_instance == nullptr)
    {
      _instance = new RoomsModel();
    }
    return _instance;
  }

public:
  int rowCount(const QModelIndex& parent) const;
  QVariant data(const QModelIndex& index, int role) const;

private:
  ScheduleModel* _scheduleModel;

private:
  static RoomsModel* _instance;
};

#endif // ROOMSMODEL_H

#ifndef SCHEDULEMODEL_H
#define SCHEDULEMODEL_H

#include <QAbstractTableModel>

#include <src/data/DatabaseHandler.h>


class ScheduleModel : public QAbstractTableModel
{
  ScheduleModel();
public:
  static ScheduleModel* instance()
  {
    if (_instance == nullptr)
    {
      _instance = new ScheduleModel();
    }
    return _instance;
  }

public:
  int rowCount(const QModelIndex& parent) const;
  int columnCount(const QModelIndex& parent) const;
  QVariant data(const QModelIndex& index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  QSize span(const QModelIndex& index) const;

private:
  ReservationPtr findReservation(const QModelIndex& index) const;

private:
  DatabaseHandler* _dbhandler;

private:
  static ScheduleModel* _instance;
};

#endif // SCHEDULEMODEL_H

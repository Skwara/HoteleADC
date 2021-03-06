#ifndef SCHEDULEMODEL_H
#define SCHEDULEMODEL_H

#include <QAbstractTableModel>

#include <src/data/DataHandler.h>


class ScheduleModel : public QAbstractTableModel
{
  ScheduleModel();
public:
  static ScheduleModel* instance()
  {
    return &_instance;
  }

public:
  int rowCount(const QModelIndex& parent) const;
  int columnCount(const QModelIndex& parent) const;
  QVariant data(const QModelIndex& index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  QSize span(const QModelIndex& index) const;

  QDate sourceDate(int col) const;
  RoomPtr sourceRoom(int row) const;

  ReservationPtr getReservation(const QModelIndex& index) const;
  bool deleteReservation(const QModelIndex& index) const;

private:
  DataHandler* _dataHandler;

private:
  static ScheduleModel _instance;
};

#endif // SCHEDULEMODEL_H

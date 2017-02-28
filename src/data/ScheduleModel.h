#ifndef SCHEDULEMODEL_H
#define SCHEDULEMODEL_H

#include <QAbstractTableModel>

#include <src/data/DatabaseHandler.h>


// TODO Remove singleton, set model in MainWindow
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

private:
  ReservationPtr findReservation(const QModelIndex& index) const;

private:
  DatabaseHandler* _dbhandler;

private:
  static ScheduleModel _instance;
};

#endif // SCHEDULEMODEL_H

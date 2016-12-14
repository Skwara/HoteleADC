#ifndef SCHEDULEVIEW_H
#define SCHEDULEVIEW_H

#include <QTableView>


class ScheduleTableView : public QTableView
{
public:
  ScheduleTableView(QWidget* parent = nullptr);

public:
  void setModel(QAbstractItemModel* model);
};

#endif // SCHEDULEVIEW_H

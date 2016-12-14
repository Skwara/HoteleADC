#ifndef SCHEDULEVIEW_H
#define SCHEDULEVIEW_H

#include <QTableView>


class ScheduleView : public QTableView
{
public:
  ScheduleView(QWidget* parent = nullptr);

public:
  void setModel(QAbstractItemModel* model);
};

#endif // SCHEDULEVIEW_H

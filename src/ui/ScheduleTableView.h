#ifndef SCHEDULEVIEW_H
#define SCHEDULEVIEW_H

#include <QTableView>


class ScheduleTableView : public QTableView
{
  Q_OBJECT

public:
  explicit ScheduleTableView(QWidget* parent = nullptr);
  ~ScheduleTableView();

public:
  void setModel(QAbstractItemModel* model);

public slots:
  void updateSpan();

private:
  const int _horizontalHeaderWidth = 30;
  const int _horizontalHeaderHeight = 40;
  const int _verticalHeaderWidth = 30;
  const int _verticalHeaderHeight = 20;
};

#endif // SCHEDULEVIEW_H

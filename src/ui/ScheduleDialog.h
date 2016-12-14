#ifndef SCHEDULEDIALOG_H
#define SCHEDULEDIALOG_H

#include <QDialog>

#include "src/ui/ScheduleTableView.h"


namespace Ui {
class ScheduleDialog;
}

class ScheduleDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ScheduleDialog(QWidget* parent = 0);
  ~ScheduleDialog();

private:
  Ui::ScheduleDialog* ui;
  ScheduleTableView* _scheduleTableView;

};

#endif // SCHEDULEDIALOG_H

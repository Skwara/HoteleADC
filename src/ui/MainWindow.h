#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/ui/ScheduleTableView.h"
#include "data/DatabaseHandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

private slots:
  void on_newReservationButton_clicked();
  void on_scheduleButton_clicked();
  void on_dockWidget_topLevelChanged(bool isFloating);

private:
  Ui::MainWindow* ui;
  ScheduleTableView* _scheduleTableView;

  DatabaseHandler* _dbHandler;
};

#endif // MAINWINDOW_H

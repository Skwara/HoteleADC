#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/ui/ScheduleTableView.h"
#include "data/DataHandler.h"
#include "NewReservation/NewReservationDialogInterface.h"

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
  void on_newBatchButton_clicked();
  void on_dockWidget_topLevelChanged(bool isFloating);

private:
  Ui::MainWindow* ui;
  ScheduleTableView* _scheduleTableView;

  DataHandler* _dataHandler;
};

#endif // MAINWINDOW_H

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "NewReservationDialog.h"
#include "ScheduleDialog.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , _scheduleTableView(new ScheduleTableView(this))
  , _dbHandler(DatabaseHandler::instance())
{
  ui->setupUi(this);

  ui->dockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
  ui->dockWidget->setWidget(_scheduleTableView);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_newReservationButton_clicked()
{
  NewReservationDialog* dialog = new NewReservationDialog(this);
  connect(_scheduleTableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
          dialog, SLOT(scheduleSelectionChanged(QItemSelection,QItemSelection)));
  dialog->show();
}

void MainWindow::on_scheduleButton_clicked()
{
  ScheduleDialog* dialog = new ScheduleDialog(this);
  dialog->show();
}

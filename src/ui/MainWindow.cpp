#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "NewReservationDialog.h"
#include "ScheduleDialog.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , _dbHandler(DatabaseHandler::instance())
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_newReservationButton_clicked()
{
  NewReservationDialog* dialog = new NewReservationDialog(this);
  dialog->show();
}

void MainWindow::on_scheduleButton_clicked()
{
  ScheduleDialog* dialog = new ScheduleDialog(this);
  dialog->show();
}

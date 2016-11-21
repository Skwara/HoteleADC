#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "NewReservationDialog.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_newReservationButton_clicked()
{
  NewReservationDialog* dialog = new NewReservationDialog();
  dialog->show();
}

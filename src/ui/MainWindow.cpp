#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "ui/NewReservation/NewSingleDialog.h"
#include "ui/NewReservation/NewBatchDialog.h"


MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , _scheduleTableView(new ScheduleTableView(this))
  , _dbHandler(DatabaseHandler::instance())
{
  ui->setupUi(this);

  ui->dockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
  ui->dockWidget->setWidget(_scheduleTableView);
  connect(ui->dockWidget, SIGNAL(topLevelChanged(bool)), this, SLOT(on_dockWidget_topLevelChanged(bool)));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_newReservationButton_clicked()
{
  NewSingleDialog* dialog = new NewSingleDialog(this);
  connectNewDialog(dialog);
  dialog->show();
}

void MainWindow::on_newBatchButton_clicked()
{
  NewBatchDialog* dialog = new NewBatchDialog(this);
  connectNewDialog(dialog);
  dialog->show();
}

void MainWindow::on_dockWidget_topLevelChanged(bool isFloating)
{
  if (isFloating)
  {
    ui->dockWidget->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint);
    ui->dockWidget->show();
  }
}

void MainWindow::connectNewDialog(NewReservationDialogInterface* dialog)
{
  connect(_scheduleTableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
          dialog, SLOT(scheduleSelectionChanged(QItemSelection,QItemSelection)));
  connect(dialog, SIGNAL(reservationSaved()), _scheduleTableView, SLOT(updateSpan()));
}

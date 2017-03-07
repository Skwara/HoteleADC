#include "ScheduleTableView.h"

#include <QHeaderView>
#include <QMenu>
#include <QMessageBox>

#include "data/ScheduleModel.h"
#include "ui/NewReservation/NewSingleDialog.h"
#include "ui/NewReservation/NewBatchDialog.h"


// For QSet<RoomPtr>
template <typename T>
unsigned int qHash(const std::shared_ptr<T>& ptr, unsigned int seed = 0)
{
    return qHash(ptr.get(), seed);
}

ScheduleTableView::ScheduleTableView(QWidget* parent)
  : QTableView(parent)
{
  setObjectName(QStringLiteral("scheduleTableView"));
  setFrameShape(QFrame::Box);
  setLineWidth(0);
  setMidLineWidth(1);

  //TODO Remove 1 pixel move of contents to horizontal header
  setModel(ScheduleModel::instance());

  horizontalHeader()->setMinimumSectionSize(_horizontalHeaderWidth);
  horizontalHeader()->setMaximumSectionSize(horizontalHeader()->minimumSectionSize());
  horizontalHeader()->setFixedHeight(_horizontalHeaderHeight);
  horizontalHeader()->setStyleSheet("QHeaderView{ border: 0px; border-bottom: 1px solid lightgrey; border-left: 1px solid lightgrey; }");
  resizeColumnsToContents();

  verticalHeader()->setMinimumSectionSize(_verticalHeaderHeight);
  verticalHeader()->setMaximumSectionSize(verticalHeader()->minimumSectionSize());
  verticalHeader()->setFixedWidth(_verticalHeaderWidth);
  verticalHeader()->setStyleSheet("QHeaderView{ border: 0px; border-right: 1px solid lightgrey; border-top: 1px solid lightgrey; }");
  resizeRowsToContents();

  setSelectionMode(QAbstractItemView::ExtendedSelection);

  connect(this->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onSelectionChanged(QItemSelection,QItemSelection)));
}

ScheduleTableView::~ScheduleTableView()
{
  model()->deleteLater();
}

void ScheduleTableView::setModel(QAbstractItemModel* model)
{
  QTableView::setModel(model);
  updateSpan();
}

void ScheduleTableView::updateSpan()
{
  clearSpans();
  for (int row = 0; row < this->model()->rowCount(); ++row)
  {
    for (int col = 0; col < this->model()->columnCount(); ++col)
    {
      QSize span = this->model()->span(this->model()->index(row, col));
      if (span.height() > 1 || span.width() > 1)
      {
        this->setSpan(row, col, span.height(), span.width());
      }
    }
  }
}

void ScheduleTableView::contextMenuEvent(QContextMenuEvent* event)
{
  QMenu* menu = new QMenu(this);
  QActionGroup* actionGroup = new QActionGroup(menu);

  foreach (QString actionName, actions())
  {
    QAction* action = new QAction(actionName, menu);
    action->setData(indexAt(event->pos()));
    actionGroup->addAction(action);
    menu->addAction(action);
  }

  connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(onContextMenuActionTriggered(QAction*)));
  menu->popup(viewport()->mapToGlobal(event->pos()));
}

void ScheduleTableView::onSelectionChanged(const QItemSelection& /*selected*/, const QItemSelection& /*deselected*/)
{
  QSet<QModelIndex> allSelected = this->selectionModel()->selectedIndexes().toSet();
  QList<RoomPtr> selectedRooms = getSelectedRooms(allSelected);
  QPair<QDate, QDate> beginEndDates = getSelectedBeginEndDates(allSelected);

  emit roomSelectionChanged(selectedRooms);
  emit dateSelectionChanged(beginEndDates);
}

void ScheduleTableView::onContextMenuActionTriggered(QAction* action)
{
  QModelIndex index = action->data().value<QModelIndex>();
  if (action->text() == actions()[Edit])
  {
    ReservationPtr reservation = ScheduleModel::instance()->getReservation(index);
    NewReservationDialogInterface* dialog;
    if (reservation->isBatch())
      dialog = new NewBatchDialog(this, reservation);
    else
      dialog = new NewSingleDialog(this, reservation);

    connect(this->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            dialog, SLOT(scheduleSelectionChanged(QItemSelection,QItemSelection)));
    connect(dialog, SIGNAL(reservationSaved()), this, SLOT(updateSpan()));
    dialog->show();
  }
  else if (action->text() == actions()[Delete])
  {
    // TODO Check if reservation has more rooms and ask for deletion of room or whole reservation.
    if (QMessageBox::question(this, "Usunięcie rezerwacji", "Jesteś pewny?", QMessageBox::Cancel | QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok)
    {
      if (!ScheduleModel::instance()->deleteReservation(index))
        QMessageBox::critical(this, "Błąd", "Usunięcie rezerwacji nie powiodło się", QMessageBox::Ok);
      updateSpan();
    }
  }
}

QList<RoomPtr> ScheduleTableView::getSelectedRooms(QSet<QModelIndex> allSelected)
{
  QSet<RoomPtr> selectedRooms;
  foreach (QModelIndex index, allSelected)
    selectedRooms += ScheduleModel::instance()->sourceRoom(index.row());

  return selectedRooms.toList();
}

QPair<QDate, QDate> ScheduleTableView::getSelectedBeginEndDates(QSet<QModelIndex> allSelected)
{
  QPair<int, int> beginEndCols((*allSelected.begin()).column(), (*allSelected.begin()).column());
  foreach (QModelIndex index, allSelected)
  {
    beginEndCols.first = std::min(beginEndCols.first, index.column());
    beginEndCols.second = std::max(beginEndCols.second, index.column());
  }

  return QPair<QDate, QDate>(ScheduleModel::instance()->sourceDate(beginEndCols.first),
                                 ScheduleModel::instance()->sourceDate(beginEndCols.second + 1)); // On schedule leave date is not selected
}

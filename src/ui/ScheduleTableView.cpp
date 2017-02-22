#include "ScheduleTableView.h"

#include "src/data/ScheduleModel.h"

#include <QHeaderView>


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

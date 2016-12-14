#include "src/ui/ScheduleView.h"

ScheduleView::ScheduleView(QWidget* parent)
  : QTableView(parent)
{

}

void ScheduleView::setModel(QAbstractItemModel* model)
{
  QTableView::setModel(model);

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

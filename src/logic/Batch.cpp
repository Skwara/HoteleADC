#include "Batch.h"


Batch::Batch(QDate beginDate, QDate endDate, QStringList buildings)
  : _beginDate(beginDate)
  , _endDate(endDate)
  , _buildings(buildings)
{
}

QDate Batch::beginDate() const
{
  return _beginDate;
}

QDate Batch::endDate() const
{
  return _endDate;
}

QStringList Batch::buildings() const
{
  return _buildings;
}

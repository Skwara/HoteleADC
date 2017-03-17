#include "BatchDateModel.h"


BatchDateModel::BatchDateModel()
  : _dataHandler(DataHandler::instance())
{
}

int BatchDateModel::rowCount(const QModelIndex& /*parent*/) const
{
  return _dataHandler->batchPeriods().size();
}

int BatchDateModel::columnCount(const QModelIndex& /*parent*/) const
{
  return columns().size();
}

QVariant BatchDateModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  if (role == Qt::DisplayRole)
  {
    switch (index.column())
    {
    case 0:
      return sourceBatch(index.row())->beginDate().toString(Qt::SystemLocaleShortDate);
    case 1:
      return sourceBatch(index.row())->endDate().toString(Qt::SystemLocaleShortDate);
    case 2:
      return sourceBatch(index.row())->buildings().join(", ");
    default:
      return QVariant();
    }
  }

  return QVariant();
}

QVariant BatchDateModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal)
  {
    if (role == Qt::DisplayRole)
    {
      return columns()[section];
    }
  }
  return QVariant();
}

BatchPtr BatchDateModel::sourceBatch(int row) const
{
  return _dataHandler->batchPeriod(row);
}

#ifndef BATCHDATEMODEL_H
#define BATCHDATEMODEL_H

#include <QAbstractTableModel>

#include "data/DatabaseHandler.h"


class BatchDateModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  BatchDateModel();

  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  int columnCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  BatchPtr sourceData(int row) const;

private:
  static const QStringList columns()
  {
    static const QStringList columns = {"Od", "Do", "Budynki"};
    return columns;
  }

private:
  DatabaseHandler* _dbHandler;
};

#endif // BATCHDATEMODEL_H

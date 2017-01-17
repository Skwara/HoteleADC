#ifndef SUMMARYMODEL_H
#define SUMMARYMODEL_H

#include <QAbstractTableModel>
#include <QString>

#include "logic/Reservation.h"


class SummaryModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  SummaryModel(Reservation& reservation);

  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  int columnCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role) const;

private:
  static const int _rowCount = 8;
  static const QString rowName(int row)
  {
    static const QString rows[_rowCount] = {"Ilość dni",
                                            "Ilość pokoi",
                                            "Ilość osób",
                                            "Ilość pustych",
                                            "Koszt pokoju",
                                            "Koszt pustych",
                                            "Koszt parkingu",
                                            "Koszt całkowity"};
    return rows[row];
  }

  QVariant rowValue(int row) const;

  Reservation& _reservation;
};

#endif // SUMMARYMODEL_H

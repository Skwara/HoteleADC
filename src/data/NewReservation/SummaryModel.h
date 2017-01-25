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

  bool setData(const QModelIndex& index, const QVariant& value, int role);
  Qt::ItemFlags flags(const QModelIndex& index) const;

private:
  QVariant rowValue(int row) const;
  QVariant rowEditValue(int row) const;
  QVariant formatPrice(PricePair price) const;
  QVariant formatDiscount(double discount) const;

private:
  static const int _rowCount = 11;
  static const QString rowName(int row)
  {
    static const QString rows[_rowCount] = {"Ilość dni",
                                            "Ilość pokoi",
                                            "Ilość osób",
                                            "Ilość pustych",
                                            "Ilość dostawek",
                                            "Koszt pokoju",
                                            "Koszt pustych",
                                            "Koszt dostawek",
                                            "Koszt parkingu",
                                            "Koszt całkowity",
                                            "Rabat"};
    return rows[row];
  }
  bool isRowEditable(int row) const { return row >= 5; }

  Reservation& _reservation;

};

#endif // SUMMARYMODEL_H

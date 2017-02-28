#ifndef PARTICIPANTSMODEL_H
#define PARTICIPANTSMODEL_H

#include <QAbstractTableModel>

#include "ParticipantsSpinBoxDelegate.h"
#include "logic/Reservation.h"


class ParticipantsModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  ParticipantsModel(ReservationPtr reservation);

public:
  ParticipantsSpinBoxDelegate& delegate();

  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  int columnCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  bool setData(const QModelIndex& index, const QVariant& value, int role);
  Qt::ItemFlags flags(const QModelIndex& index) const;

private:
  static const QStringList columns()
  {
    static const QStringList columns = {"Pokój", "Osoby", "Dostawki"};
    return columns;
  }

  ParticipantsSpinBoxDelegate _spinBoxDelegate;

private:
  ReservationPtr _reservation;
};

#endif // PARTICIPANTSMODEL_H

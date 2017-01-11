#ifndef PARTICIPANTSMODEL_H
#define PARTICIPANTSMODEL_H

#include <QAbstractTableModel>

#include "SpinBoxDelegate.h"
#include "logic/Reservation.h"


class ParticipantsModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  ParticipantsModel(Reservation& reservation);

public:
  SpinBoxDelegate& delegate();

  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  int columnCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  Qt::ItemFlags flags(const QModelIndex& index) const;
  bool setData(const QModelIndex& index, const QVariant& value, int role);

private:
  SpinBoxDelegate _spinBoxDelegate;

private:
  Reservation& _reservation;

};

#endif // PARTICIPANTSMODEL_H

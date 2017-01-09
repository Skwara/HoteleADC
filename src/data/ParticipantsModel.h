#ifndef PARTICIPANTSMODEL_H
#define PARTICIPANTSMODEL_H

#include <QAbstractTableModel>
#include <QItemSelectionModel>

#include "RoomsModel.h"


class ParticipantsModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  ParticipantsModel(Reservation& reservation);

public:
  int rowCount(const QModelIndex& parent) const;
  int columnCount(const QModelIndex& parent) const;
  QVariant data(const QModelIndex& index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
  Reservation& _reservation;

};

#endif // PARTICIPANTSMODEL_H

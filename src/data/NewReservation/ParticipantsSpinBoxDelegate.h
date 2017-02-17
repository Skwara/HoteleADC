#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QStyledItemDelegate>

#include "logic/Reservation.h"


class ParticipantsSpinBoxDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  ParticipantsSpinBoxDelegate(ReservationPtr reservation, QObject* parent = 0);

  QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
  void setEditorData(QWidget* editor, const QModelIndex& index) const;
  void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
  void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;

private:
  ReservationPtr _reservation;
};

#endif // SPINBOXDELEGATE_H

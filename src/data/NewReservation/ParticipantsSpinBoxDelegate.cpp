#include "ParticipantsSpinBoxDelegate.h"

#include <QSpinBox>


ParticipantsSpinBoxDelegate::ParticipantsSpinBoxDelegate(Reservation& reservation, QObject* parent)
  : QStyledItemDelegate(parent)
  , _reservation(reservation)
{
}

QWidget* ParticipantsSpinBoxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& /*option*/, const QModelIndex& index) const
{
  QSpinBox *editor = new QSpinBox(parent);
  editor->setFrame(false);
  editor->setMinimum(0);
  editor->setMaximum(_reservation.rooms()[index.row()]->maxParticipants());

  return editor;
}

void ParticipantsSpinBoxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
  int value = index.model()->data(index, Qt::EditRole).toInt();

  QSpinBox* spinBox = qobject_cast<QSpinBox*>(editor);
  spinBox->setValue(value);
}

void ParticipantsSpinBoxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  QSpinBox* spinBox = qobject_cast<QSpinBox*>(editor);
  spinBox->interpretText();
  int value = spinBox->value();

  model->setData(index, value, Qt::EditRole);
}

void ParticipantsSpinBoxDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& /*index*/) const
{
  editor->setGeometry(option.rect);
}

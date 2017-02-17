#ifndef NEWBATCHDIALOG_H
#define NEWBATCHDIALOG_H

#include <QDialog>


namespace Ui {
class NewBatchDialog;
}

class NewBatchDialog : public QDialog
{
  Q_OBJECT

public:
  explicit NewBatchDialog(QWidget* parent = 0);
  ~NewBatchDialog();

private:
  Ui::NewBatchDialog* ui;
};

#endif // NEWBATCHDIALOG_H

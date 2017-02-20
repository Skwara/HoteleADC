#ifndef SINGLEDATEGROUPBOX_H
#define SINGLEDATEGROUPBOX_H

#include <QGroupBox>

#include "data/DatabaseHandler.h"


namespace Ui {
class SingleDateGroupBox;
}

class SingleDateGroupBox : public QGroupBox
{
  Q_OBJECT

public:
  explicit SingleDateGroupBox(ReservationPtr reservation, QWidget* parent = 0);
  ~SingleDateGroupBox();

public slots:
  void update(QSet<int> selectedCols);

private:
  void setup();

private slots:
  void onBeginCalendarWidgetClicked(const QDate &date);
  void onEndCalendarWidgetClicked(const QDate &date);
private:
  void setEndDateToBeginDate();

private:
  Ui::SingleDateGroupBox* ui;
  DatabaseHandler* _dbHandler;

  ReservationPtr _reservation;
};

#endif // SINGLEDATEGROUPBOX_H

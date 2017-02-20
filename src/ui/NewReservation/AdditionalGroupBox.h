#ifndef ADDITIONALGROUPBOX_H
#define ADDITIONALGROUPBOX_H

#include <QGroupBox>

#include "data/DatabaseHandler.h"


namespace Ui {
class AdditionalGroupBox;
}

class AdditionalGroupBox : public QGroupBox
{
  Q_OBJECT

public:
  explicit AdditionalGroupBox(ReservationPtr reservation, QWidget* parent = 0);
  ~AdditionalGroupBox();

public slots:
  void update();

private:
  void setup();

private slots:
  void onParkingCheckBoxToggled(bool checked);
  void onEmptyPlaceCheckBoxToggled(bool checked);

private:
  Ui::AdditionalGroupBox* ui;
  DatabaseHandler* _dbHandler;

  ReservationPtr _reservation;
};

#endif // ADDITIONALGROUPBOX_H

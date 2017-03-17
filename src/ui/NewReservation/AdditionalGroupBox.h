#ifndef ADDITIONALGROUPBOX_H
#define ADDITIONALGROUPBOX_H

#include <QGroupBox>

#include "data/DataHandler.h"


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
  DataHandler* _dataHandler;

  ReservationPtr _reservation;
};

#endif // ADDITIONALGROUPBOX_H

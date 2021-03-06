#ifndef PARTICIPANTSGROUPBOX_H
#define PARTICIPANTSGROUPBOX_H

#include <QGroupBox>

#include "data/DataHandler.h"
#include "data/NewReservation/ParticipantsModel.h"


namespace Ui {
class ParticipantsGroupBox;
}

class ParticipantsGroupBox : public QGroupBox
{
  Q_OBJECT

public:
  explicit ParticipantsGroupBox(ReservationPtr reservation, QWidget* parent = 0);
  ~ParticipantsGroupBox();

public slots:
  void update();

private:
  void setup();

private:
  Ui::ParticipantsGroupBox* ui;
  DataHandler* _dataHandler;

  ReservationPtr _reservation;
  ParticipantsModel _participantsModel;
};

#endif // PARTICIPANTSGROUPBOX_H

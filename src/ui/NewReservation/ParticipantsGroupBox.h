#ifndef PARTICIPANTSGROUPBOX_H
#define PARTICIPANTSGROUPBOX_H

#include <QGroupBox>

#include "data/DatabaseHandler.h"
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

  void update();

private:
  void setup();

private:
  Ui::ParticipantsGroupBox* ui;
  DatabaseHandler* _dbHandler;

  ReservationPtr _reservation;
  ParticipantsModel _participantsModel;
};

#endif // PARTICIPANTSGROUPBOX_H

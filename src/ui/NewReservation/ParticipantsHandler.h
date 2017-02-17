#ifndef PARTICIPANTSHANDLER_H
#define PARTICIPANTSHANDLER_H

#include <QObject>

#include "data/DatabaseHandler.h"
#include "data/NewReservation/ParticipantsModel.h"


namespace Ui {
class NewSingleDialog;
}

class ParticipantsHandler : public QObject
{
  Q_OBJECT

public:
  explicit ParticipantsHandler(Ui::NewSingleDialog* ui, ReservationPtr reservation, QObject* parent = 0);

  void setup();

public slots:
  void update();

private:
  Ui::NewSingleDialog* ui;
  DatabaseHandler* _dbHandler;

  ReservationPtr _reservation;
  ParticipantsModel _participantsModel;
};

#endif // PARTICIPANTSHANDLER_H

#ifndef PARTICIPANTSHANDLER_H
#define PARTICIPANTSHANDLER_H

#include <QObject>

#include "data/DatabaseHandler.h"
#include "data/ParticipantsModel.h"


namespace Ui {
class NewReservationDialog;
}

class ParticipantsHandler : public QObject
{
  Q_OBJECT

public:
  explicit ParticipantsHandler(Ui::NewReservationDialog* ui, Reservation& reservation, QObject* parent = 0);

  void setup();

public slots:
  void update();

private:
  Ui::NewReservationDialog* ui;
  DatabaseHandler* _dbHandler;

  ParticipantsModel _participantsModel;
};

#endif // PARTICIPANTSHANDLER_H

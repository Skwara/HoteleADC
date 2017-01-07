#ifndef PARTICIPANTSHANDLER_H
#define PARTICIPANTSHANDLER_H

#include <QObject>

#include "data/DatabaseHandler.h"


namespace Ui {
class NewReservationDialog;
}

class ParticipantsHandler : public QObject
{
  Q_OBJECT

public:
  explicit ParticipantsHandler(Ui::NewReservationDialog* ui, QObject* parent = 0);

  void setup();
  void prepare();

private:
  Ui::NewReservationDialog* ui;
  DatabaseHandler* _dbHandler;
};

#endif // PARTICIPANTSHANDLER_H

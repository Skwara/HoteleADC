#ifndef MAINGROUPBOX_H
#define MAINGROUPBOX_H

#include <QGroupBox>
#include <QLineEdit>

#include "data/DatabaseHandler.h"
#include "logic/Reservation.h"


namespace Ui {
class MainGroupBox;
}

class MainGroupBox : public QGroupBox
{
  Q_OBJECT

public:
  explicit MainGroupBox(ReservationPtr reservation, QWidget* parent = 0);
  ~MainGroupBox();

  ClientPtr createClient() const;

  QString surname() const;
  QString name() const;
  QString street() const;

public slots:
  void update();

private:
  void setup();

  void addCompleter(QLineEdit* lineEdit, QSet<QString> completions);
  void fillRemainingClientData(QString surname, QString name = "", QString street = "");

private slots:
  void onSurnameLineEditEditingFinished();
  void onNameLineEditEditingFinished();
  void onStreetLineEditEditingFinished();

private:
  Ui::MainGroupBox* ui;
  DatabaseHandler* _dbHandler;

  ReservationPtr _reservation;
};

#endif // MAINGROUPBOX_H

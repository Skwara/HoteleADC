#ifndef MAINHANDLER_H
#define MAINHANDLER_H

#include <QObject>
#include <QLineEdit>
#include <QSet>

#include "data/DatabaseHandler.h"


namespace Ui {
class NewReservationDialog;
}

class MainHandler : public QObject
{
  Q_OBJECT

public:
  MainHandler(Ui::NewReservationDialog* ui, QObject* parent = 0);

  void setup();
  void prepare();

public slots:
  void surnameLineEditEditingFinished();
  void nameLineEditEditingFinished();
  void streetLineEditEditingFinished();

private:
  void addCompleter(QLineEdit* lineEdit, QSet<QString> completions);
  void fillRemainingClientData(QString surname, QString name = "", QString street = "");

private:
  Ui::NewReservationDialog* ui;
  DatabaseHandler* _dbHandler;
};

#endif // MAINHANDLER_H

#ifndef MAINHANDLER_H
#define MAINHANDLER_H

#include <QObject>
#include <QLineEdit>
#include <QSet>

#include "data/DatabaseHandler.h"


namespace Ui {
class NewSingleDialog;
}

class MainHandler : public QObject
{
  Q_OBJECT

public:
  explicit MainHandler(Ui::NewSingleDialog* ui, QObject* parent = 0);

  void setup();

  ClientPtr createClient() const;

public slots:
  void update();

private slots:
  void onSurnameLineEditEditingFinished();
  void onNameLineEditEditingFinished();
  void onStreetLineEditEditingFinished();

private:
  void addCompleter(QLineEdit* lineEdit, QSet<QString> completions);
  void fillRemainingClientData(QString surname, QString name = "", QString street = "");

private:
  Ui::NewSingleDialog* ui;
  DatabaseHandler* _dbHandler;
};

#endif // MAINHANDLER_H

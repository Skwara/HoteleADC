#include "MainHandler.h"
#include "ui_NewReservationDialog.h"

#include "logic/Client.h"

#include <QCompleter>


MainHandler::MainHandler(Ui::NewReservationDialog* ui, QObject* parent)
  : QObject(parent)
  , ui(ui)
  , _dbHandler(DatabaseHandler::instance())
{
}

void MainHandler::setup()
{
  QSet<QString> surnames;
  foreach (ClientPtr client, _dbHandler->clients())
  {
    surnames << client->surname();
  }
  addCompleter(ui->surnameLineEdit, surnames);

  connect(ui->surnameLineEdit, SIGNAL(editingFinished()), this, SLOT(onSurnameLineEditEditingFinished()));
  connect(ui->nameLineEdit, SIGNAL(editingFinished()), this, SLOT(onNameLineEditEditingFinished()));
  connect(ui->streetLineEdit, SIGNAL(editingFinished()), this, SLOT(onStreetLineEditEditingFinished()));
}

void MainHandler::prepare()
{
}

void MainHandler::onSurnameLineEditEditingFinished()
{
  QString surname = ui->surnameLineEdit->text();
  if (!surname.isEmpty())
  {
    Client::firstLetterUppercase(surname);
    ui->surnameLineEdit->setText(surname);
    fillRemainingClientData(surname);
  }
}

void MainHandler::onNameLineEditEditingFinished()
{
  QString surname = ui->surnameLineEdit->text();
  QString name = ui->nameLineEdit->text();
  if (!name.isEmpty())
  {
    Client::firstLetterUppercase(name);
    ui->nameLineEdit->setText(name);
    fillRemainingClientData(surname, name);
  }
}

void MainHandler::onStreetLineEditEditingFinished()
{
  QString surname = ui->surnameLineEdit->text();
  QString name = ui->nameLineEdit->text();
  QString street = ui->streetLineEdit->text();
  if (!street.isEmpty())
  {
    Address::correctStreetFormatting(street);
    ui->streetLineEdit->setText(street);
    fillRemainingClientData(surname, name, street);
  }
}

void MainHandler::addCompleter(QLineEdit* lineEdit, QSet<QString> completions)
{
  if (completions.isEmpty())
    return;

  if (completions.size() == 1)
  {
    lineEdit->setText(*completions.begin());
  }

  QCompleter* completer = new QCompleter(completions.toList(), this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  completer->setFilterMode(Qt::MatchContains);
  lineEdit->setCompleter(completer);
}

void MainHandler::fillRemainingClientData(QString surname, QString name, QString street)
{
  QList<ClientPtr> matchingClients  = _dbHandler->clients(surname, name, street);
  QSet<QString> names;
  QSet<QString> streets;
  foreach (ClientPtr client, matchingClients)
  {
    names << client->name();
    streets << client->address().street();
  }
  if (name.isEmpty())
  {
    addCompleter(ui->nameLineEdit, names);
  }
  if (name.isEmpty() && street.isEmpty())
  {
    addCompleter(ui->streetLineEdit, streets);
  }

  if (matchingClients.size() == 1)
  {
    const ClientPtr& client = matchingClients.first();
    ui->surnameLineEdit->setText(client->surname());
    ui->nameLineEdit->setText(client->name());
    ui->streetLineEdit->setText(client->address().street());
    ui->numberLineEdit->setText(client->address().number());
    ui->postalCodeLineEdit->setText(client->address().postalCode());
    ui->cityLineEdit->setText(client->address().city());
    ui->countryLineEdit->setText(client->address().country());
    ui->phoneLineEdit->setText(client->phone());
    ui->emailLineEdit->setText(client->eMail());
  }
}

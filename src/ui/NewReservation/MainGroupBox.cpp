#include "MainGroupBox.h"
#include "ui_MainGroupBox.h"

#include <QCompleter>

#include "logic/Client.h"


MainGroupBox::MainGroupBox(ReservationPtr reservation, QWidget* parent)
  : QGroupBox(parent)
  , ui(new Ui::MainGroupBox)
  , _dbHandler(DatabaseHandler::instance())
  , _reservation(reservation)
{
  ui->setupUi(this);
  setup();
}

MainGroupBox::~MainGroupBox()
{
  delete ui;
}

ClientPtr MainGroupBox::createClient() const
{
  return std::make_shared<Client>(ui->surnameLineEdit->text(),
                                  ui->nameLineEdit->text(),
                                  Address(ui->streetLineEdit->text(),
                                          ui->numberLineEdit->text(),
                                          ui->postalCodeLineEdit->text(),
                                          ui->cityLineEdit->text(),
                                          ui->countryLineEdit->text()),
                                  ui->phoneLineEdit->text(),
                                  ui->emailLineEdit->text());
}

QString MainGroupBox::surname() const
{
  return ui->surnameLineEdit->text();
}

QString MainGroupBox::name() const
{
  return ui->nameLineEdit->text();
}

QString MainGroupBox::street() const
{
  return ui->streetLineEdit->text();
}

void MainGroupBox::update()
{
  ClientPtr client = _reservation->client();
  if (client)
  {
    ui->surnameLineEdit->setText(client->surname());
    ui->nameLineEdit->setText(client->name());
    Address address = client->address();
    ui->streetLineEdit->setText(address.street());
    ui->numberLineEdit->setText(address.number());
    ui->postalCodeLineEdit->setText(address.postalCode());
    ui->cityLineEdit->setText(address.city());
    ui->countryLineEdit->setText(address.country());
    ui->phoneLineEdit->setText(client->phone());
    ui->emailLineEdit->setText(client->eMail());
  }
}

void MainGroupBox::setup()
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

  update();
}

void MainGroupBox::addCompleter(QLineEdit* lineEdit, QSet<QString> completions)
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

void MainGroupBox::fillRemainingClientData(QString surname, QString name, QString street)
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

void MainGroupBox::onSurnameLineEditEditingFinished()
{
  QString surname = ui->surnameLineEdit->text();
  if (!surname.isEmpty())
  {
    Client::firstLetterUppercase(surname);
    ui->surnameLineEdit->setText(surname);
    fillRemainingClientData(surname);
  }
}

void MainGroupBox::onNameLineEditEditingFinished()
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

void MainGroupBox::onStreetLineEditEditingFinished()
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

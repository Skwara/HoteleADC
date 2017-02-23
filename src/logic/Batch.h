#ifndef BATCH_H
#define BATCH_H

#include <memory>

#include <QDate>


class Batch // TODO BATCH Extract reservation interface
{
public:
  Batch(QDate beginDate, QDate endDate, QStringList buildings);

  QDate beginDate() const;
  QDate endDate() const;
  QStringList buildings() const;

private:
  QDate _beginDate;
  QDate _endDate;
  QStringList _buildings;
};

using BatchPtr = std::shared_ptr<Batch>;

#endif // BATCH_H

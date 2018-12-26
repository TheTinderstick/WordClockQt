#ifndef QWORDCLOCK_H
#define QWORDCLOCK_H

#include <QObject>
#include "wordclock.h"
#include <QTimer>

class QWordClock : public QObject
{
  Q_OBJECT
public:
  explicit QWordClock(QObject *parent = nullptr);

signals:

public slots:
  void timerInterval();

private:
  WordClock itsWordClock;
  QTimer itsTimer;
};

#endif // QWORDCLOCK_H

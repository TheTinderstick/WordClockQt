#include "qwordclock.h"
#include <QTime>

QWordClock::QWordClock(QObject *parent) : QObject(parent), itsTimer(this)
{
  //itsTimer.callOnTimeout(SLOT(timerInterval()));
  QObject::connect( &itsTimer, SIGNAL(timeout()), this, SLOT(timerInterval()) );
  itsTimer.start(1000);
}

void QWordClock::timerInterval()
{
  auto theTime {QTime::currentTime()};
  auto minutes {theTime.minute()};
  auto hours {theTime.hour()};
  WordClock::WordList myWords = itsWordClock.getTimeInWords(hours, minutes);
}

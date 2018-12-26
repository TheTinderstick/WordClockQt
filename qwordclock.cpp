#include "qwordclock.h"
#include <QTime>
#include <QDebug>

QWordClock::QWordClock(QObject *parent) : QObject(parent), itsTimer(this)
{
  QObject::connect( &itsTimer, SIGNAL(timeout()), this, SLOT(timerInterval()) );
  itsTimer.start(1000);

  /* for now in ctor => move to language change */
  m_clockWords.clear();
  WordClock::ClockWords myClock{ itsWordClock.getClockWords() };
  for( auto word : myClock )
  {
    QString aWord{ word.c_str() };
    m_clockWords.append( aWord.toLatin1().toUpper() );
  }
//  for( auto word : m_clockWords )
//  {
//    qDebug() << word;
//  }
}

//QQmlListProperty<QString> QWordClock::clockWords()
//{
//  return QQmlListProperty<QString>(
//        this,
//        this,
//        &QWordClock::clockWordCount,
//        &QWordClock::clockWordAt
//        );
//}

QVector<QString> QWordClock::clockWords()
{
  return m_clockWords;
}

int QWordClock::clockWordCount() const
{
  return m_clockWords.length();
}

const QString& QWordClock::clockWordAt(int index) const
{
  return m_clockWords.at(index);
}

void QWordClock::timerInterval()
{
  auto theTime {QTime::currentTime()};
  auto minutes {theTime.minute()};
  auto hours {theTime.hour()};
  WordClock::WordList myWords = itsWordClock.getTimeInWords(hours, minutes);
  if( lastTimeInWords != myWords )
  {
    m_timeInWords.clear();
    for( auto word : myWords )
    {
      m_timeInWords.append( word );
    }
    emit timeInWordsChanged();
  }
}

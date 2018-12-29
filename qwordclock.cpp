#include "qwordclock.h"
#include <QTime>
#include <QDebug>
#include <cmath>
#include <iostream>

const QString QWordClock::randomChars{"ABCDEFGHIJKLMNOPRSTUW"};

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

  calculateClockLayout();
}

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

const QWordClock::TClock& QWordClock::clockLayout() const
{
  return m_clockLayout;
}

int QWordClock::clockSize() const
{
  return m_clockSize;
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

void QWordClock::calculateClockLayout()
{
  int sumWordLength = 0;
  for( auto word : m_clockWords )
  {
    sumWordLength += word.length();
  }
  double sqrtOfSize = sqrt( static_cast<double>(sumWordLength) );
  int minSquare = ceil(sqrtOfSize);
  qDebug() << "min square:" << minSquare;

  TClock theClock;

  /* iterate and try fitting the words into a square of letters */
  /* if they dont fit make the square larger */
  for( auto size=minSquare; size<clockWordCount(); ++size ) {
    int currentRow = 0;
    int processed = 0;
    QVector<int> remainingInRow(size, size);
    QVector<int> wordRowMap(clockWordCount());
    TClockRow aClockRow;
    TClock aClock(size, aClockRow);
    for( int i=0; i<clockWordCount(); ++i )
    {
      auto word{m_clockWords.at(i)};
      if( word.length() <= remainingInRow.at(currentRow) )
      {
        /* word fits in current row => add it */
        wordRowMap[i] = currentRow;
        remainingInRow[currentRow] -= word.length();
        bool firstChar=true;
        for( auto c : word )
        {
          QClockLetter *clockChar = new QClockLetter(c,i);
          if(firstChar)
          {
            clockChar->setWordStart(true);
            firstChar = false;
          }
          aClock[currentRow].append( clockChar );
        }
        processed++;
      }
      else
      {
        /* word does not fit in current row */
        currentRow++;
        if(currentRow >= size ||
           word.length() > remainingInRow.at(currentRow))
        {
          /* we are over maximum size
           * or we have a word that is longer
           * than a row  => increase the size and start over */
          break;
        }
        else
        {
          /* add the word to the next row */
          wordRowMap[i] = currentRow;
          remainingInRow[currentRow] -= word.length();
          bool firstChar=true;
          for( auto c : word )
          {
            QClockLetter *clockChar = new QClockLetter(c,i);
            if(firstChar)
            {
              clockChar->setWordStart(true);
              firstChar = false;
            }
            aClock[currentRow].append(clockChar);
          }
          processed++;
        }
      }
    }
    if( processed == clockWordCount() )
    {
      m_wordRowMap.clear();
      m_wordRowMap = wordRowMap;
      m_clockSize = size;
      theClock = aClock;
      break;
    }
  }

  /* randomly fill remaining free spaces between words */
  std::srand(std::time(nullptr));
  for( auto& row : theClock )
  {
    if( row.length() < m_clockSize )
    {
      /* create random chars and insert randomly */
      auto neededChars = m_clockSize - row.length();
      for( int i=0; i<neededChars; ++i )
      {
        QChar aRandomChar = randomChars.at(std::rand()%randomChars.length());
        QClockLetter *aChar = new QClockLetter(aRandomChar);
        /* check for insert spots */
        QVector< TClockRow::iterator > insertSpots;
        insertSpots.append( row.end() );
        TClockRow::iterator iter;
        for (iter = row.begin(); iter != row.end(); ++iter)
        {
          if( (*iter)->isWordStart() )
          {
            insertSpots.append( iter );
          }
        }
        iter = insertSpots.at(std::rand()%insertSpots.length());
        row.insert(iter, aChar);
      }
    }
  }

  for( auto row : theClock ) {
    for( auto c : row ) {
      std::cout << c->m_clockChar.toLatin1();
    }
    std::cout << std::endl;
  }
  m_clockLayout = theClock;
  emit clockLayoutChanged();
}

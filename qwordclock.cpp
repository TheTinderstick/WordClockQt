#include "qwordclock.h"
#include <QTime>
#include <QDebug>
#include <cmath>
#include <iostream>

const QString QWordClock::randomChars{"ABCDEFGHIJKLMNOPRSTUW"};

QWordClock::QWordClock(QObject *parent) : QObject(parent), itsTimer(this)
{
  QObject::connect( &itsTimer, SIGNAL(timeout()), this, SLOT(timerInterval()) );

  /* for now in ctor => move to language change */
  m_clockWords.clear();
  WordClock::ClockWords myClock{ itsWordClock.getClockWords() };
  for( auto word : myClock )
  {
    QString aWord{ word.c_str() };
    m_clockWords.append( aWord.toLatin1().toUpper() );
  }

  calculateClockLayout();

  /* run timerInterval once to initiakize time */
  timerInterval();

  /* now start cyclic timer */
  itsTimer.start(1000);
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

QQmlListProperty<QClockLetter> QWordClock::clockLayout()
{
  return QQmlListProperty<QClockLetter>(this, this,
                                        &QWordClock::clockLayoutCount,
                                        &QWordClock::clockLayoutAt);
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
  updateClockTime();
}

void QWordClock::updateClockTime()
{
  for( auto& row : m_clockLayout )
  {
    for( auto c : row )
    {
      auto wordIndex = c->wordIndex();
      auto iterator = std::find_if(m_timeInWords.begin(),
                                   m_timeInWords.end(),
                                   [wordIndex](int item){ return item==wordIndex;});
      if( iterator != m_timeInWords.end() )
      {
        c->setActive(true);
      }
      else
      {
        c->setActive(false);
      }
    }
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

  TClock theClock;

  /* iterate and try fitting the words into a square of letters */
  /* if they dont fit make the square larger */
  for( auto size=minSquare; size<clockWordCount(); ++size ) {
    int currentRow = 0;
    int processed = 0;
    QVector<int> remainingInRow(size, size);
    TClockRow aClockRow;
    TClock aClock(size, aClockRow);
    for( int i=0; i<clockWordCount(); ++i )
    {
      auto word{m_clockWords.at(i)};
      if( word.length() <= remainingInRow.at(currentRow) )
      {
        /* word fits in current row => add it */
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
      std::cout << c->clockChar().toLatin1();
    }
    std::cout << std::endl;
  }
  m_clockLayout.clear();
  m_clockLayout = theClock;
  emit clockLayoutChanged();
}

int QWordClock::clockLayoutCount(QQmlListProperty<QClockLetter>* list)
{
  auto size = reinterpret_cast< QWordClock* >(list->data)->clockSize();
  return size*size;
}

QClockLetter* QWordClock::clockLayoutAt(QQmlListProperty<QClockLetter>* list, int index)
{
  auto *wordClock = reinterpret_cast< QWordClock* >(list->data);
  auto row = index / wordClock->clockSize();
  auto col = index - (row*wordClock->clockSize());
  return wordClock->clockLayoutAt(row, col);
}

QClockLetter* QWordClock::clockLayoutAt(int row, int col)
{
  return m_clockLayout.at(row).at(col);
}

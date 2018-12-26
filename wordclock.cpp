#include "wordclock.h"

#include <QDebug>

WordClock::WordClock()
{
  constructGerman();
  updateWords();
}

void WordClock::updateWords()
{
  auto theTime {QTime::currentTime()};
  auto minutes {theTime.minute()};
  auto hours {theTime.hour()};
  qDebug() << "Time:" << theTime.toString();
  qDebug() << hours << ":" << minutes;

  auto timeInWords = update( hours, minutes );
  for( int index : timeInWords )
  {
    qDebug() << clockWords.at(index).c_str();
  }
}

void WordClock::constructEnglish()
{
  clockWords.clear();
  clockWords =
  {
    "it", "is", "half", "ten", "quarter",
    "twenty", "five", "to", "past",
    "one", "three", "two", "four", "five",
    "six", "seven", "eight", "nine", "ten",
    "eleven", "twelve", "o'clock"
  };

  /* xx:00 - xx:05 => It is x oClock */
  /* xx:05 - xx:10 => It is five past x */
  /* xx:10 - xx:15 => It is ten past x */
  /* xx:15 - xx:20 => It is quarter past x */
  /* xx:20 - xx:25 => It is twenty past x */
  /* xx:25 - xx:30 => It is twenty five past x */
  /* xx:30 - xx:35 => It is half past x */
  /* xx:35 - xx:40 => It is twenty five to x+1 */
  /* xx:40 - xx:45 => It is twenty to x+1 */
  /* xx:45 - xx:50 => It is quarter to x+1 */
  /* xx:50 - xx:55 => It is ten to x+1 */
  /* xx:55 - yy:00 => It is five to x+1 */
}

void WordClock::constructGerman()
{
  clockWords.clear();
  clockWords = {
    "es",
    "ist",
    "viertel",
    "zehn",
    "zwanzig",
    "fuenf",
    "nach",
    "vor",
    "halb",
    "zwoelf",
    "eins",
    "zwei",
    "drei",
    "vier",
    "fuenf",
    "sechs",
    "elf",
    "sieben",
    "acht",
    "neun",
    "zehn",
    "uhr",
  };

  auto getMinuteWords = [](uint8_t hours, uint8_t minutes) {
    std::list<int> wordList;
    int hourWordIndex = -1;
    wordList.push_back(0); /* Es */
    wordList.push_back(1); /* ist */
    if(5 > minutes)
    {
      hourWordIndex = 2; /* X */
      wordList.push_back(21); /* Uhr */
    }
    else if( 10 > minutes)
    {
      wordList.push_back(5); /* fuenf */
      wordList.push_back(6); /* nach */
      hourWordIndex = 4; /* X */
    }
    else if( 15 > minutes)
    {
      wordList.push_back(3); /* zehn */
      wordList.push_back(6); /* nach */
      hourWordIndex = 4; /* X */
    }
    else if( 20 > minutes)
    {
      wordList.push_back(2); /* viertel */
      wordList.push_back(6); /* nach */
      hourWordIndex = 4; /* X */
    }
    else if( 25 > minutes)
    {
      wordList.push_back(4); /* zwanzig */
      wordList.push_back(6); /* nach */
      hourWordIndex = 4; /* X */
    }
    else if( 30 > minutes)
    {
      wordList.push_back(5); /* fuenf */
      wordList.push_back(7); /* vor */
      wordList.push_back(8); /* halb */
      hourWordIndex = 5; /* X+1 */
    }
    else if( 35 > minutes)
    {
      wordList.push_back(8); /* halb */
      hourWordIndex = 3; /* X+1 */
    }
    else if( 40 > minutes)
    {
      wordList.push_back(5); /* fuenf */
      wordList.push_back(6); /* nach */
      wordList.push_back(8); /* halb */
      hourWordIndex = 5; /* X+1 */
    }
    else if( 45 > minutes)
    {
      wordList.push_back(4); /* zwanzig */
      wordList.push_back(7); /* nach */
      hourWordIndex = 4; /* X+1 */
    }
    else if( 50 > minutes)
    {
      wordList.push_back(2); /* viertel */
      wordList.push_back(7); /* vor */
      hourWordIndex = 4; /* X+1 */
    }
    else if( 55 > minutes)
    {
      wordList.push_back(3); /* zehn */
      wordList.push_back(7); /* vor */
      hourWordIndex = 4; /* X+1 */
    }
    else if( 60 > minutes)
    {
      wordList.push_back(5); /* fuenf */
      wordList.push_back(7); /* vor */
      hourWordIndex = 4; /* X+1 */
    }
    else
    {
      abort();
    }
    return std::make_pair(wordList,hourWordIndex);
  };
  auto getHourWords = [](uint8_t hours, uint8_t minutes){
    uint8_t theHour = hours;
    if(25 >= minutes)
    {
      theHour += 1;
    }
    theHour = theHour%12;
    int wordIndex = -1;
    switch(theHour) {
      case 0: wordIndex = 9; break; /* zwoelf */
      case 1: wordIndex = 10; break; /* eins */
      case 2: wordIndex = 11; break; /* zwei */
      case 3: wordIndex = 12; break; /* drei */
      case 4: wordIndex = 13; break; /* vier */
      case 5: wordIndex = 14; break; /* fuenf */
      case 6: wordIndex = 15; break; /* sechs */
      case 7: wordIndex = 17; break; /* sieben */
      case 8: wordIndex = 18; break; /* acht */
      case 9: wordIndex = 19; break; /* neun */
      case 10: wordIndex = 20; break; /* zehn */
      case 11: wordIndex = 16; break; /* elf */
      default: abort(); break;
    }
    return wordIndex;
  };
  auto getWords = [&getHourWords,&getMinuteWords](uint8_t hours, uint8_t minutes) {
    auto hourResult = getHourWords(hours, minutes);
    auto minuteResult = getMinuteWords(hours, minutes);
    std::list<int> result;
    for (auto wordIndex : minuteResult.first) {
      result.push_back(wordIndex);
    }
    auto it = result.begin();
    advance(it, minuteResult.second);
    result.insert(it,hourResult);
    return result;
  };

  update = getWords;

  /* xx:00 - xx:05 => Es ist x Uhr */
  /* xx:05 - xx:10 => Es ist fuenf nach x */
  /* xx:10 - xx:15 => Es ist zehn nach x */
  /* xx:15 - xx:20 => Es ist viertel nach x */
  /* xx:20 - xx:25 => Es ist zwanzig nach x */
  /* xx:25 - xx:30 => Es ist fuenf vor halb x+1 */
  /* xx:30 - xx:35 => Es ist halb x+1 */
  /* xx:35 - xx:40 => Es ist fuenf nach halb x+1 */
  /* xx:40 - xx:45 => Es ist zwanzig vor x+1 */
  /* xx:45 - xx:50 => Es ist viertel vor x+1 */
  /* xx:50 - xx:55 => Es ist zehn vor x+1 */
  /* xx:55 - yy:00 => Es ist fuenf vor x+1 */
}

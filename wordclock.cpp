#include "wordclock.h"

#include <QDebug>

WordClock::WordClock()
{
  constructEnglish();
  updateWords();
}

void WordClock::updateWords()
{
  auto theTime {QTime::currentTime()};
  auto minutes {theTime.minute()};
  auto hours {theTime.hour()};
  qDebug() << "Time:" << theTime.toString();
  qDebug() << hours << ":" << minutes;
  int minuteRange {minutes / 5};
  qDebug() << "minuteRange:" << minuteRange;

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
  clockWords =
  {
    "es", "ist", "viertel", "zehn", "zwanzig",
    "fuenf", "nach", "vor", "halb", "zwoelf",
    "eins", "zwei", "drei", "vier", "fuenf",
    "sechs", "elf", "sieben", "acht", "neun",
    "zehn", "uhr"
  };

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

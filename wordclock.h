#ifndef WORDCLOCK_H
#define WORDCLOCK_H

#include <QTime>
#include <vector>
#include <list>
#include <functional>

class WordClock
{
public:
  typedef std::list<int> WordList;
  typedef std::vector<std::string> ClockWords;
  WordClock();
  WordList getTimeInWords(uint8_t hours, uint8_t minutes);
  ClockWords getClockWords();
private:  
  ClockWords clockWords;
  void constructEnglish();
  void constructGerman();
  std::function< WordList(uint8_t, uint8_t)> update;
};

#endif // WORDCLOCK_H

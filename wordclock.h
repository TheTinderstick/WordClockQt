#ifndef WORDCLOCK_H
#define WORDCLOCK_H

#include <QTime>
#include <vector>
#include <list>
#include <functional>

class WordClock
{
public:
  WordClock();
private:
  typedef std::list<int> WordList;
  std::vector<std::string> clockWords;
  void updateWords();
  void constructEnglish();
  void constructGerman();
  std::function< WordList(uint8_t, uint8_t)> update;
};

#endif // WORDCLOCK_H

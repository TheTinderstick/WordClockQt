#ifndef WORDCLOCK_H
#define WORDCLOCK_H

#include <QTime>
#include <vector>

class WordClock
{
public:
  WordClock();
private:
  std::vector<std::string> clockWords;
  void updateWords();
  void constructEnglish();
  void constructGerman();
};

#endif // WORDCLOCK_H

#ifndef QWORDCLOCK_H
#define QWORDCLOCK_H

#include <QObject>
#include "wordclock.h"
#include <QTimer>
#include <QVector>
#include <QQmlListProperty>

class QWordClock : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QVector<QString> clockWords READ clockWords NOTIFY clockWordsChanged)
  Q_PROPERTY(QVector<int> timeInWords NOTIFY timeInWordsChanged)

public:
  explicit QWordClock(QObject *parent = nullptr);
  QVector<QString> clockWords();
  Q_INVOKABLE int clockWordCount() const;
  const QString& clockWordAt(int index) const;

signals:
  void clockWordsChanged();
  void timeInWordsChanged();

public slots:
  void timerInterval();

private:
  WordClock itsWordClock;
  WordClock::WordList lastTimeInWords;
  QTimer itsTimer;
  QVector<QString> m_clockWords;
  QVector<int> m_timeInWords;
};

#endif // QWORDCLOCK_H

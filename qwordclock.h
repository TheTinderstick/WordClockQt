#ifndef QWORDCLOCK_H
#define QWORDCLOCK_H

#include <QObject>
#include "wordclock.h"
#include "qclockletter.h"
#include <QTimer>
#include <QVector>
#include <QString>

class QWordClock : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QVector<QString> clockWords READ clockWords NOTIFY clockWordsChanged)
  Q_PROPERTY(QVector<int> timeInWords NOTIFY timeInWordsChanged)
  Q_PROPERTY(TClock clockLayout READ clockLayout NOTIFY clockLayoutChanged)

public:
  typedef QVector< QClockLetter* > TClockRow;
  typedef QVector< TClockRow > TClock;

  explicit QWordClock(QObject *parent = nullptr);
  QVector<QString> clockWords();
  Q_INVOKABLE int clockWordCount() const;
  const QString& clockWordAt(int index) const;
  Q_INVOKABLE int clockSize() const;
  const TClock& clockLayout() const;

signals:
  void clockWordsChanged();
  void timeInWordsChanged();
  void clockLayoutChanged();

public slots:
  void timerInterval();

private:
  WordClock itsWordClock;
  WordClock::WordList lastTimeInWords;
  QTimer itsTimer;
  QVector<QString> m_clockWords;
  QVector<int> m_wordRowMap;
  QVector<int> m_timeInWords;
  uint8_t m_clockSize;
  TClock m_clockLayout;

  static const QString randomChars;

  void calculateClockLayout();
};

#endif // QWORDCLOCK_H

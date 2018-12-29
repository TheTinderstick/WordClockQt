#ifndef QCLOCKLETTER_H
#define QCLOCKLETTER_H

#include <QObject>

class QClockLetter : public QObject
{
  Q_OBJECT
public:
  explicit QClockLetter(QObject *parent = nullptr);
  explicit QClockLetter(QChar aChar, QObject *parent = nullptr);
  explicit QClockLetter(QChar aChar, uint8_t aWordIndex, QObject *parent = nullptr);

  void setWordStart(bool isWordStart);
  bool isWordStart();

  QChar m_clockChar;
  bool m_wordStart;
  uint8_t m_wordIndex;
signals:

public slots:
};

#endif // QCLOCKLETTER_H

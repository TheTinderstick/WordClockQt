#ifndef QCLOCKLETTER_H
#define QCLOCKLETTER_H

#include <QObject>

class QClockLetter : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QChar clockChar READ clockChar CONSTANT)
  Q_PROPERTY(int wordIndex READ wordIndex CONSTANT)
public:
  explicit QClockLetter(QObject *parent = nullptr);
  explicit QClockLetter(QChar aChar, QObject *parent = nullptr);
  explicit QClockLetter(QChar aChar, uint8_t aWordIndex, QObject *parent = nullptr);

  void setWordStart(bool isWordStart);
  bool isWordStart();

  const QChar& clockChar() const;
  int wordIndex() const;

private:
  QChar m_clockChar;
  bool m_wordStart;
  uint8_t m_wordIndex;

signals:

public slots:
};

#endif // QCLOCKLETTER_H

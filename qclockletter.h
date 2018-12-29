#ifndef QCLOCKLETTER_H
#define QCLOCKLETTER_H

#include <QObject>

class QClockLetter : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QChar clockChar READ clockChar CONSTANT)
  Q_PROPERTY(int wordIndex READ wordIndex CONSTANT)
  Q_PROPERTY(bool active READ isActive NOTIFY activeChanged)
public:
  explicit QClockLetter(QObject *parent = nullptr);
  explicit QClockLetter(QChar aChar, QObject *parent = nullptr);
  explicit QClockLetter(QChar aChar, uint8_t aWordIndex, QObject *parent = nullptr);

  void setWordStart(bool isWordStart);
  bool isWordStart();

  const QChar& clockChar() const;
  int wordIndex() const;
  bool isActive() const;
  void setActive(bool isActive);

private:
  QChar m_clockChar;
  bool m_wordStart;
  uint8_t m_wordIndex;
  bool m_active;

signals:
  void activeChanged();

public slots:
};

#endif // QCLOCKLETTER_H

#include "qclockletter.h"

QClockLetter::QClockLetter(QObject *parent) : QObject(parent),
  m_clockChar('_'),
  m_wordIndex(UINT8_MAX),
  m_wordStart(false)
{

}

QClockLetter::QClockLetter(QChar aChar, QObject *parent) : QObject(parent),
  m_clockChar(aChar),
  m_wordIndex(UINT8_MAX),
  m_wordStart(false)
{

}

QClockLetter::QClockLetter(QChar aChar, uint8_t aWordIndex, QObject *parent) : QObject(parent),
  m_clockChar(aChar),
  m_wordIndex(aWordIndex),
  m_wordStart(false)
{

}

void QClockLetter::setWordStart(bool isWordStart)
{
  m_wordStart = isWordStart;
}

bool QClockLetter::isWordStart()
{
  return m_wordStart;
}

const QChar& QClockLetter::clockChar() const
{
  return m_clockChar;
}

int QClockLetter::wordIndex() const
{
  return m_wordIndex;
}

bool QClockLetter::isActive() const
{
  return m_active;
}

void QClockLetter::setActive(bool isActive)
{
  bool changed = (m_active != isActive);
  m_active = isActive;
  if( changed ) emit activeChanged();
}

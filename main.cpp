#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "wordclock.h"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
  {
    return -1;
  }

  WordClock wordClock{};

  return app.exec();
}

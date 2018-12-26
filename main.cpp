#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qwordclock.h"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
  {
    return -1;
  }

  QWordClock wordClock{};

  return app.exec();
}

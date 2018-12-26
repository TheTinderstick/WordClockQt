#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "qwordclock.h"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  qmlRegisterType<QWordClock>("QWordClock", 1, 0, "WordClock");

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
  {
    return -1;
  }

  QWordClock wordClock{};

  return app.exec();
}

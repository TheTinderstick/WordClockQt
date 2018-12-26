import QtQuick 2.8
import QtQuick.Window 2.2
import QWordClock 1.0

Window {
  visible: true
  width: 640
  height: 480
  title: qsTr("WordClock")

  WordClock {
    id: wordClock
  }

  Row {
    anchors.fill: parent
    Repeater {
      model: wordClock.clockWordCount()
      Text {
        visible: true
        text: wordClock.clockWords[index]
        color: "black"
      }
    }
  }

}

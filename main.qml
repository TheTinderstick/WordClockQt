import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QWordClock 1.0
import QClockLetter 1.0

Window {
  id: mainWindow
  visible: true
  width: 640
  height: 640
  title: qsTr("WordClock")

  WordClock {
    id: wordClock
  }

  GridLayout {
    id: theGrid
    anchors.fill: parent
    columns: wordClock.clockSize()
    Repeater {
      model: wordClock.clockSize()*wordClock.clockSize()
      Rectangle {
        width: mainWindow.width / theGrid.columns
        height: mainWindow.height / theGrid.columns
        border.width: 2
        border.color: "red"
        Text {
          anchors.fill: parent
          text: wordClock.clockLayout[index].clockChar
          color: "black"
          fontSizeMode: Text.Fit
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
        }
      }
    }
  }
}

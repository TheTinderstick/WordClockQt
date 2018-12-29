import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import QWordClock 1.0
import QClockLetter 1.0

Window {
  id: mainWindow
  visible: true
  width: 60*wordClock.clockSize()
  height: 60*wordClock.clockSize()
  title: qsTr("WordClock")

  WordClock {
    id: wordClock
  }

  Rectangle {
    color: "lightgrey"
    anchors.fill: parent

    GridLayout {
      id: theGrid
      anchors.fill: parent
      columns: wordClock.clockSize()
      columnSpacing: 0
      rowSpacing: 0
      Repeater {
        model: wordClock.clockSize()*wordClock.clockSize()
        Rectangle {
          id: letterRectangle
          width: mainWindow.width / theGrid.columns
          height: mainWindow.height / theGrid.columns
          color: "lightgrey"
          Text {
            id: letterText
            text: wordClock.clockLayout[index].clockChar
            anchors.fill: parent
            color: wordClock.clockLayout[index].active?"white":"grey"
            font.pixelSize: 72
            font.family: "Times New Roman"
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
          }
          Glow {
            anchors.fill: parent
            visible: wordClock.clockLayout[index].active?true:false
            radius: 8
            samples: 17
            color: "lightblue"
            source: letterText
          }
        }
      }
    }
  }
}

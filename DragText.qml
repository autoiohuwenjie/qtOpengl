import QtQuick 2.8
import QtQml.Models 2.2

Rectangle {
    width: 200; height: 100

    DelegateModel {
        id: visualModel
        model: ListModel {
            ListElement { name: "Apple" }
            ListElement { name: "Orange" }
        }
        delegate: Rectangle {
            height: 25
            width: 100
            Text { text: "Name: " + name}
        }
    }

    ListView {
        anchors.fill: parent
        model: visualModel
    }
}

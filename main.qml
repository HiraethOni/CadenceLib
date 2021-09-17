import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import com.hmqs.sqlqml 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("CadenceLib")
    id: root

    NumberAnimation {
        id: numberAnimation
    }
    Button {
        id: add_btn
        text: qsTr("Add Items")
        anchors.left: parent.left
        anchors.top: parent.top
    }
    Button {
        id: del_btn
        text: qsTr("Delete Itmes")
        anchors.left: add_btn.right
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    Button {
        id: ser_btn
        text: qsTr("Search")
        anchors.left: del_btn.right
        anchors.top: parent.top
        anchors.leftMargin: 0
    }

    TableView {
        id: tableView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: add_btn.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 0
        width: parent.width
        model: TableModel {
            TableModelColumn {
                display: "name"
            }
            TableModelColumn {
                display: "color"
            }

            rows: [{
                    "name": "cat",
                    "color": "black"
                }, {
                    "name": "dog",
                    "color": "brown"
                }]
        }

        delegate: Rectangle {
            border.width: 1

            Text {
                text: display
                anchors.centerIn: parent
            }
        }
    }
    Button {
        id: save_btn
        text: qsTr("Save Changes")
        anchors.left: ser_btn.right
        anchors.top: parent.top
        anchors.leftMargin: 0
        anchors.topMargin: 0

        onClicked: {
//            databaseCtrl.getAllTablesNames()
        }
    }

    ComboBox {
        id: tables_box
        anchors.left: save_btn.right
        anchors.top: parent.top
        anchors.leftMargin: 0
        anchors.topMargin: 0
        model: ListModel {
            ListElement {
                key: "First"
                value: 123
            }
            ListElement {
                key: "Second"
                value: 456
            }
            ListElement {
                key: "Third"
                value: 789
            }
        }
    }
}

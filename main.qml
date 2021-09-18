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
    property var mma: dbc.getAllContent("capacitor")
    DatabaseCtrl{
        id:dbc;
    }

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
        onClicked: {
            console.log(mma)
        }
    }

    TableView {
        id: tableView
        anchors.left: parent.left
        anchors.top: add_btn.bottom
        anchors.bottom: parent.bottom
        columnSpacing: 1
        rowSpacing: 1
        width: parent.width
        clip: true
        model: TableModel {
            TableModelColumn {display: "ID"}
            TableModelColumn {display: "Part Number"}
            TableModelColumn {display: "Description"}
            TableModelColumn {display: "Part Type"}
            TableModelColumn {display: "Value"}
            TableModelColumn {display: "MFG Name"}
            TableModelColumn {display: "PCB Footprint"}
            TableModelColumn {display: "Symbol"}
            TableModelColumn {display: "MFG Part Name"}
            TableModelColumn {display: "MFG Part Description"}
            TableModelColumn {display: "RoHS"}
            TableModelColumn {display: "MFG Part Lifecycle Phase"}
            TableModelColumn {display: "Datasheet"}
            TableModelColumn {display: "buy link"}

            // Each row is one type of fruit that can be ordered
            rows: JSON.parse(mma)
        }
        delegate: DelegateChooser {
//            DelegateChoice {
//                column: 0
//                delegate: CheckBox {
//                    checked: model.display
//                    onToggled: model.display = checked
//                }
//            }
//            DelegateChoice {
//                column: 1
//                delegate: SpinBox {
//                    value: model.display
//                    onValueModified: model.display = value
//                }
//            }
            DelegateChoice {
                delegate: TextField {
                    text: model.display
                    selectByMouse: true
                    implicitWidth: 50
                    onAccepted: model.display = text
                }
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
            console.log(dbc.getAllContent("capacitor"))
        }
    }

    ComboBox {
        id: tables_box
        anchors.left: save_btn.right
        anchors.top: parent.top
        anchors.leftMargin: 0
        anchors.topMargin: 0
        model: dbc.getAllTablesNames()
    }
}

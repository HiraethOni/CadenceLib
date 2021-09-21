import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import com.hmqs.sqlqml 1.0

Window {
    width: 720
    height: 480
    visible: true
    title: qsTr("CadenceLib")
    id: root
    property var db_data: dbc.getAllContent("capacitor")
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
        }
    }

    TableView {
        id: tableView
        anchors.left: parent.left
        anchors.top: add_btn.bottom
        anchors.bottom: parent.bottom
        rowSpacing: 1
        anchors.right: parent.right
        clip: true
        columnWidthProvider: function (column) {
            return tableView.model ? tableView.width/tableView.model.columnCount() : 0
        }
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

            rows: JSON.parse(db_data)
        }

        delegate: DelegateChooser {
//            DelegateChoice {
//                column: 0
//                delegate: Label {
//                    text: model.display
//                }
//            }

            DelegateChoice {
                delegate: TextField {
                    implicitWidth: 80
                    text: model.display
                    selectByMouse: true
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
            console.info(tableView.model.rows)
        }
    }

    ComboBox {
        id: tables_box
        anchors.left: save_btn.right
        anchors.top: parent.top
        anchors.leftMargin: 0
        anchors.topMargin: 0
        model: dbc.getAllTablesNames()
        onCurrentTextChanged: {
            console.info(currentText)
            db_data = dbc.getAllContent(currentText)
        }
    }
}

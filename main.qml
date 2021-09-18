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
    }

    Component{
        id:tableview_delegate
        Item{
            id:wrapper;
            Column{
                Text{text:display}
                Button{text:display}
            }
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
//        clip: true

        model: TableModel {
            TableModelColumn {
                display: "checked"
            }
            TableModelColumn {
                display: "amount"
            }
            TableModelColumn {
                display: "fruitType"
            }
            TableModelColumn {
                display: "fruitName"
            }
            TableModelColumn {
                display: "fruitPrice"
            }

            // Each row is one type of fruit that can be ordered
            rows: [{
                    "checked"// Each property is one cell/column.
                    : false,
                    "amount": 1,
                    "fruitType": "Apple",
                    "fruitName": "Granny Smith",
                    "fruitPrice": 1.50
                }, {
                    "checked": true,
                    "amount": 4,
                    "fruitType": "Orange",
                    "fruitName": "Navel",
                    "fruitPrice": 2.50
                }, {
                    "checked": false,
                    "amount": 1,
                    "fruitType": "Banana",
                    "fruitName": "Cavendish",
                    "fruitPrice": 3.50
                }]
        }
        delegate: DelegateChooser {
            DelegateChoice {
                column: 0
                delegate: CheckBox {
                    checked: model.display
                    onToggled: model.display = checked
                }
            }
            DelegateChoice {
                column: 1
                delegate: SpinBox {
                    value: model.display
                    onValueModified: model.display = value
                }
            }
            DelegateChoice {
                delegate: TextField {
                    text: model.display
                    selectByMouse: true
                    implicitWidth: 140
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

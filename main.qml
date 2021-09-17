import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import com.hmqs.sqlqml 1.0
import com.hmqs.tablemodel 1.0

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
        anchors.right: parent.right
        anchors.top: add_btn.bottom
        anchors.bottom: parent.bottom
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        model: TableModel{}

        delegate: tableview_delegate
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

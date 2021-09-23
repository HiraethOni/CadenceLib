import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Window {
    visible: true
    title: qsTr("CadenceLib")
    id: root

    Row {
        anchors.fill:parent
        ComboBox {
            id: table_class
            height: 50
        }
        Button {
            id: add_btn
            text: qsTr("Add")
            height: table_class.height
        }

        TextField {
            id: partNumber
            height: table_class.height
            placeholderText: qsTr("Part Number")
        }
    }
}

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Window {
    visible: true
    title: qsTr("CadenceLib")
    id: root
    width: 720
    height: 480

    Flow {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.fill: parent
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        anchors.topMargin: 5

        spacing: 10

        ComboBox {
            id: table_class
            editable: true
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
        TextField {
            id: description
            height: table_class.height
            placeholderText: qsTr("Description")
        }
        ComboBox {
            id: part_type
            editable: true
            height: table_class.height
        }
        TextField {
            id: _value
            height: table_class.height
            placeholderText: qsTr("Value")
        }
        TextField {
            id: mfg_name
            height: table_class.height
            placeholderText: qsTr("MFG Name")
        }
        ComboBox {
            id: pcb_footprint
            editable: true
            height: table_class.height
        }
        ComboBox {
            id: symbol
            editable: true
            height: table_class.height
        }
        TextField {
            id: mfg_part_name
            height: table_class.height
            placeholderText: qsTr("MFG Part Name")
        }
        TextField {
            id: mfg_part_des
            height: table_class.height
            placeholderText: qsTr("MFG Part Description")
        }
        ComboBox {
            id: roHS
            height: table_class.height
            model: ["YES", "NO", "Unsure"]
        }
        ComboBox {
            id: mfg_part_lifeduty
            height: table_class.height
            model: ["Active", "Not For New Designs", "Obsolete"]
        }
        TextField {
            id: datasheet
            height: table_class.height
            placeholderText: qsTr("Datasheet")
        }
        TextField {
            id: buy_link
            height: table_class.height
            placeholderText: qsTr("Buy link")
        }
    }
}

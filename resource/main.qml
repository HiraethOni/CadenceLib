import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import com.hmqs.sqlqml 1.0

Window {
    visible: true
    title: qsTr("CadenceLib")
    id: root
    width: 530
    height: 480

    DataBaseCtrl {
        id: dbc
    }
    property var partType
    property var symbolVar
    ListModel {
        id:partTypeModel
        ListElement{text:"Demo"}
    }
    ListModel {
        id:symbolVarModel
        ListElement{text:"Demo"}
    }

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
            height: 50
            model: dbc.getAllTablesNames()
            onCurrentTextChanged: {
                partType = dbc.getFiledValue("Part Type",currentText)
                symbolVar = dbc.getFiledValue("Symbol", currentText)

                partTypeModel.clear()
                partType.forEach((item,index,array)=>{partTypeModel.append({text:item})})
                symbolVarModel.clear()
                symbolVar.forEach((item,index,array)=>{symbolVarModel.append({text:item})})
                part_type.currentIndex = 0
                symbol.currentIndex=0
            }
        }

        Button {
            id: add_btn
            text: qsTr("Add")
            height: table_class.height
            onClicked: {
                var add_str = []
                add_str.push(partNumber.text, description.text)
                add_str.push(part_type.currentText)
                add_str.push(_value.text, mfg_name.text)
                add_str.push(pcb_footprint.currentText, symbol.currentText)
                add_str.push(mfg_part_name.text, mfg_part_des.text)
                add_str.push(roHS.currentText, mfg_part_lifeduty.currentText)
                add_str.push(datasheet.text, buy_link.text)
                dbc.insertData(table_class.currentText, add_str)
//                console.log(add_str)
            }
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
            property var lastData: ""
            onTextChanged: {
                mfg_part_des.text = mfg_part_des.text === lastData ? text : mfg_part_des.text
                lastData = text
            }
        }
        ComboBox {
            id: part_type
            editable: true
            height: table_class.height
            model: partTypeModel
            property bool firstEnter: true

            onActiveFocusChanged: {
                if(firstEnter){
                    firstEnter = false
                    editText = ""
                } else {
                    firstEnter = true
                    editText = editText === "" ? currentText : editText
                    if (find(editText) === -1 && editText !== ""){
//                      不加上这个临时变量的话,更新Model后editText随之刷新,无法获取正确的所索引
                        var str = editText
                        model.append({text: str})
                        currentIndex = indexOfValue(str)
                    }
                }
            }
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
            model: dbc.scanPackageDir()
            property bool firstEnter: true
            onActiveFocusChanged: {
                if(firstEnter){
                    firstEnter = false
                    editText = ""
                } else {
                    firstEnter = true
                    editText = editText === "" ? currentText : editText
                }
            }
        }
        ComboBox {
            id: symbol
            editable: true
            height: table_class.height
            model: symbolVarModel
            property bool firstEnter: true
            onActiveFocusChanged: {
                if(firstEnter){
                    firstEnter = false
                    editText = ""
                } else {
                    firstEnter = true
                    editText = editText === "" ? currentText : editText
                    if (find(editText) === -1 && editText !== ""){
//                      不加上这个临时变量的话,更新Model后editText随之刷新,无法获取正确的所索引
                        var str = editText
                        model.append({text: str})
                        currentIndex = indexOfValue(str)
                    }
                }
            }
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

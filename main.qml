import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Shapes 1.15

Window {
    visible: true
    width: 1571
    height: 887
    title: "网络调试助手"

    onWidthChanged: console.log("width:",width)
    onHeightChanged: console.log("heigh:",height)

    ColumnLayout {
        anchors.fill: parent
        SplitView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            orientation: Qt.Horizontal

            //控制区
            ColumnLayout {
                SplitView.preferredWidth: 360
                SplitView.minimumWidth: 100
                SplitView.fillHeight: true

                //网络设置
                GroupBox {
                    Layout.fillWidth: true
                    Layout.margins: 5
                    title: "网络设置"

                    GridLayout {
                        columns: 2
                        anchors.left: parent.left
                        anchors.right: parent.right

                        //协议
                        Label { text: "协        议:" }
                        ComboBox {
                            id: protocolCOmboBox
                            Layout.fillWidth: true
                            model: ["UDP","TCP Client","TCP Server"]
                            onCurrentIndexChanged: {
                                if (0 === currentIndex) {
                                    startButton.text = "绑定";
                                }else if (1 === currentIndex) {
                                    startButton.text = "连接";
                                }else if (2 === currentIndex) {
                                    startButton.text = "侦听";
                                }
                            }
                        }

                        //IP
                        Label { text: "本地主机地址:" }
                        ComboBox {
                            id: ipComboBox
                            Layout.fillWidth: true
                            model: ["192.168.123.256","192.168.0.1","127.0.0.1"]
                            editable: true
                            selectTextByMouse: true
                        }

                        //端口号
                        Label { text: "本 地 端 口 :" }
                        TextField {
                            id: portTextField
                            Layout.fillWidth: true
                            text: "8000"
                            selectByMouse: true
                        }

                        //操作
                        Button {
                            id: startButton
                            Layout.columnSpan: 2
                            Layout.fillWidth: true
                            text: "绑定"
                        }
                    }
                }

                //接收设置
                GroupBox {
                    title: "接收设置"
                    Layout.fillWidth: true
                    Layout.margins: 5

                    GridLayout {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        columns: 3
                        RadioButton {           //编码类型
                            id: receivedGbkRadioButton
                            text: "GBK"
                        }
                        RadioButton {
                            id: receivedUtf8RadioButton
                            text: "UTF-8"
                            checked: true
                        }

                        RadioButton {
                            id: receivedHexRadioButton
                            text: "HEX"
                        }

                        CheckBox {          //以日志模式显示
                            id: logCheckBox
                            text: "以日志模式显示"
                            Layout.columnSpan: 3
                        }

                        CheckBox {          //自动换行
                            id: wrapCheckBox
                            text: "自动换行"
                            Layout.columnSpan: 3
                        }

                        CheckBox {          //保存为文件
                            id: saveCheckBox
                            text: "保存至文件"
                            Layout.columnSpan: 3
                        }

                        CheckBox {          //静默接收
                            id: slientReceptionCheckBox
                            text: "静默接收"
                            Layout.columnSpan: 3
                        }
                    }
                }

                //发送设置
                GroupBox {
                    Layout.fillWidth: true
                    Layout.margins: 5
                    title: "发送设置"

                    GridLayout {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        columns: 3

                        RadioButton {               //发送编码类型
                            id: sendGbkRadioButton
                            text: "GBK"
                        }

                        RadioButton {
                            id: sendUtf8RadioButton
                            text: "UTF-8"
                            checked: true
                        }

                        RadioButton {
                            id: sendHexRadioButton
                            text: "HEX"
                        }

                        CheckBox {
                            id: parseEscapeCharacters
                            text: "自动解析转义符"
                            Layout.columnSpan: 3
                        }

                        CheckBox {
                            id: checkCheckBox
                            text: "自动发送校验位"
                            Layout.columnSpan: 3
                        }

                        CheckBox {
                            id: openFileCheckBox
                            text: "打开文件数据源"
                            Layout.columnSpan: 3
                        }

                        RowLayout {
                            Layout.columnSpan: 3
                            CheckBox {
                                id: loopCheckBox
                                text: "循环周期"
                            }

                            TextField {
                                id: loopTextFiled
                                text: "1000"
                                selectByMouse: true
                                Layout.preferredWidth: 100
                                background: Shape {
                                    ShapePath {
                                        strokeColor: "#BDBDBD"
                                        strokeWidth: 1
                                        startX: 0
                                        startY: loopTextFiled.height
                                        PathLine {
                                            x:  loopTextFiled.width
                                            y: loopTextFiled.height
                                        }
                                    }
                                }
                            }

                            Label { text: "ms" }
                        }
                    }
                }

                //占位
                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }

            //数据区
            ColumnLayout {
                SplitView.fillHeight: true
                SplitView.fillWidth: true

                GroupBox {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.margins: 5
                    title: "数据接收"

                    ScrollView {
                        anchors.fill: parent
                        clip: true
                        TextArea {
                            id: receivedTextArea
                            selectByMouse: true
                            wrapMode: TextEdit.WordWrap
                        }
                    }
                }

                GroupBox {
                    id: sendGroupBox
                    Layout.fillWidth: true
                    Layout.preferredHeight: 200
                    Layout.margins: 5
                    title: "数据发送"

                    ScrollView {
                        id: sendScrollView
                        anchors.fill: parent
                        clip: true
                        TextArea {
                            id: sendTextArea
                            rightPadding: 120
                            text: "https://www.ggsd.top/"
                            selectByMouse: true
                            wrapMode: TextEdit.WrapAnywhere
                        }
                    }

                    Button {
                        id: sendButton
                        anchors.right: sendScrollView.right
                        anchors.bottom: sendScrollView.bottom
                        anchors.rightMargin: 10
                        anchors.bottomMargin: 5
                        text: "发送"
                    }

                    label: Label {
                        x: parent.leftPadding
                        width: parent.availableWidth
                        text: parent.title

                        Loader {
                            id: destAddressButton
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 100
                            sourceComponent: sendGroupBoxTabButton
                            onLoaded: item.text = "192.168.112.123:60000";
                        }

                        Loader {            //清除接收区内容
                            id: clearUpButton
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            sourceComponent: sendGroupBoxTabButton
                            onLoaded: item.text = "清屏👆";
                        }

                        Loader {            //清除发送区内容
                            id: clearDownButton
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: clearUpButton.left
                            anchors.rightMargin: 10
                            sourceComponent: sendGroupBoxTabButton
                            onLoaded: item.text = "清屏👇";
                        }

                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.minimumHeight: 50
            Layout.preferredHeight: 50

            Button {
                id: countButton
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 5
                text: "计数"
                checkable: true
                checked: true
            }

            Button {
                id: refreshCountButton
                anchors.left: countButton.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 5
                text: "重置"
            }

            Rectangle {
                anchors.left: refreshCountButton.right
                anchors.top: refreshCountButton.top
                anchors.bottom: refreshCountButton.bottom
                anchors.leftMargin: 5
                width: 300
                border.color: "lightGray"

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 5

                    //接收计数 单位：字节
                    Label {
                        id: receivedCountLabel
                        text: "RX:0"
                    }

                    //发送计数  单位：字节
                    Label {
                        id: sendCountLabel
                        text: "TX:0"
                    }
                }
            }

            //时钟
            Label {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 5
                text: new Date().toLocaleString(Qt.locale("de_DE"), "yyyy-MM-dd HH:mm:ss")

                Timer {
                    interval: 1000
                    running: true
                    repeat: true
                    onTriggered: parent.text = new Date().toLocaleString(Qt.locale("de_DE"), "yyyy-MM-dd HH:mm:ss")
                }
            }
        }
    }

    //数据发送GroupBox标题标签按钮
    Component {
        id: sendGroupBoxTabButton
        Item {
            property alias text: text.text
            width: text.width
            height: text.height
            Text {
                id: text
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        parent.font.bold = true;
                        cursorShape = Qt.PointingHandCursor;
                    }
                    onExited:  {
                        parent.font.bold = false;
                        cursorShape = Qt.ArrowCursor;
                    }
                    onPressed: {
                        parent.bottomPadding = 5;
                    }
                    onReleased:  {
                        parent.bottomPadding = 0;
                    }
                }
            }
        }
    }
}

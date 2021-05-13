import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

Window {
    id:_root
    width: 640
    height: 480
    visible: true
    title: qsTr("Image viewer")

    property var _pathToImage: "default"
    StackView{
        id:_mainStackView
        anchors.fill: parent
        initialItem: _mainPage
    }

    Page{
        id:_mainPage
        anchors.fill: parent
        Image{
            id:_image
            width: _root.width/1.1
            height: _root.height/1.1
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: (_root.width+_root.height)/200
            fillMode: Image.PreserveAspectFit
            source: _pathToImage
            Connections{
                target: appengine
                function onSetPathToImage(pathToImage) {
                    _pathToImage = pathToImage
                }
            }
        }
        Button{
            id:_showImageButton
            anchors.left: parent.left
            anchors.top: _image.bottom
            width: _root.width/9
            height: _root.height/20
            anchors.margins: (_root.width+_root.height)/200
            text: qsTr("settings")
            onClicked: {
                _mainStackView.push(_settingsPage)
            }
        }/*
        Rectangle{
            id:_formPathToImage
            anchors.left: _showImageButton.right
            anchors.top: _image.bottom
            width: _root.width/9 * 7 - (((_root.width+_root.height)/100) * 2)
            height: _root.height/20
            anchors.margins: (_root.width+_root.height)/200
            color: "#BFBFBF"
            TextInput{
                id:_pathToImageInput
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: (_root.width+_root.height)/100
                Connections
                {
                    target: appengine
                    function onSetPathToImage(pathToImage) {
                        _pathToImageInput.text = pathToImage
                    }
                }
            }
        }*/
        Button{
            id:_searchImage
            anchors.right: parent.right
            anchors.top: _image.bottom
            width: _root.width/9
            height: _root.height/20
            anchors.margins: (_root.width+_root.height)/200
            text: qsTr("search")
            onClicked: {
                //appengine.searchPicture();
                imageDialogLoad.open()
            }
        }
        FileDialog {
            id: imageDialogLoad
            folder: "."
            title: "Choose a file to open"
            selectMultiple: false
            nameFilters: [ "Image files (*.png *.jpg *.jpeg *.raw *.tiff *.jp2 *.gif)", "All files (*)" ]
            onAccepted: { _pathToImage =  imageDialogLoad.fileUrl }
        }
    }
    Page{
        id:_settingsPage
        visible: false
        anchors.fill: parent
        Rectangle{
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: (_root.width+_root.height)/200
            width: _root.width/5
            height: _root.height/15
            color:"#BFBFBF"
            radius: (_root.width+_root.height)/200
            TextInput{
                anchors.fill: parent
                font.pointSize: (_root.width+_root.height)/70
            }
        }

        Button{
            id:_backButton
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: (_root.width+_root.height)/200
            width: _root.width/9
            height: _root.height/20
            text: qsTr("back")
            onClicked: {
                _mainStackView.pop(_mainPage)
            }
        }
    }
}



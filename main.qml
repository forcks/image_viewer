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

    Connections{
        target: appengine
        function onLoadWindowsSize(x,y) {
            _root.width = x
            _root.height = y
        }
    }

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

        Button{
            id:_nextButton
            anchors.right: _searchImage.left
            anchors.top: _image.bottom
            width: _root.width/9
            height: _root.height/20
            anchors.margins: (_root.width+_root.height)/200
            text: qsTr(">")
            onClicked: {
                appengine.nextImage();
            }
        }

        Button{
            id:_prevousButton
            anchors.right: _nextButton.left
            anchors.top: _image.bottom
            width: _root.width/9
            height: _root.height/20
            anchors.margins: (_root.width+_root.height)/200
            text: qsTr("<")
            onClicked: {
                appengine.previousImage();
            }
        }



        FileDialog {
            id: imageDialogLoad
            folder: "."
            title: "Choose a file to open"
            selectMultiple: false
            nameFilters: [ "Image files (*.png *.jpg *.jpeg *.raw *.tiff *.jp2 *.gif)", "All files (*)" ]
            onAccepted: {
                _pathToImage =  imageDialogLoad.fileUrl
                appengine.setFolderPath(imageDialogLoad.folder,imageDialogLoad.fileUrl)
            }
        }
    }
    Page{
        id:_settingsPage
        visible: false
        anchors.fill: parent

        Text {
            id: _textStartSize
            text: qsTr("Window size when opened : ")
            font.pointSize: (_root.width+_root.height)/80
        }
        Text {
            id:_xText
            text: qsTr("X: ")
            font.pointSize: (_root.width+_root.height)/60
            anchors.left: parent.left
            anchors.top: _textStartSize.bottom
            anchors.margins: (_root.width+_root.height)/200
        }

        Rectangle{
            id:_xSize
            anchors.top: _textStartSize.bottom
            anchors.left: _xText.right
            anchors.margins: (_root.width+_root.height)/200
            width: _root.width/5
            height: _root.height/15
            color:"#BFBFBF"
            radius: (_root.width+_root.height)/200
            TextInput{
                id:_xSizeInput
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                maximumLength: 5
                font.pointSize: (_root.width+_root.height)/70
                validator: IntValidator {bottom: 1; top: 100000} //numbers only
            }
        }

        Text {
            id:_yText
            text: qsTr("Y: ")
            font.pointSize: (_root.width+_root.height)/60
            anchors.left: _xSize.right
            anchors.top: _textStartSize.bottom
            anchors.margins: (_root.width+_root.height)/200
        }

        Rectangle{
            id:_ySize
            anchors.top: _textStartSize.bottom
            anchors.left: _yText.right
            anchors.margins: (_root.width+_root.height)/200
            width: _root.width/5
            height: _root.height/15
            color:"#BFBFBF"
            radius: (_root.width+_root.height)/200
            TextInput{
                id:_ySizeInput
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                maximumLength: 5
                font.pointSize: (_root.width+_root.height)/70
                validator: IntValidator {bottom: 1; top: 100000} //numbers only
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

        Button{
            id:_deleteConfig
            anchors.right: _confirmButton.left
            anchors.bottom: parent.bottom
            anchors.margins: (_root.width+_root.height)/200
            width: _root.width/9
            height: _root.height/20
            text: qsTr("throw off")
            onClicked: {
                appengine.deleteConfig();
            }
        }

        Button{
            id:_confirmButton
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: (_root.width+_root.height)/200
            width: _root.width/9
            height: _root.height/20
            text: qsTr("confirm")
            onClicked: {
                appengine.saveSizeWindowWhenOpened(_xSizeInput.text,_ySizeInput.text);
            }
        }
    }
}



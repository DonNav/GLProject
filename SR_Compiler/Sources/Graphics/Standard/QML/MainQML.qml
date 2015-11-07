import QtQuick 1.1
import CustomComponents 1.0


Rectangle {
    id: root
    anchors.fill:parent
    color: "black"

    Connections
    { // Connection for resizing window content when window size change
        target:  backend
        onSizeChanged: {root.width = backend.getWidth(); root.height = backend.getHeight(); }
    }



    SharedImage
    {
        objectName: "ImageProvider"
        width: parent.width
        height: parent.height

        MouseArea {
               anchors.fill: parent
               onPressed: { GL_Manager.setMousePressEvent(mouse.x, mouse.y); colorPicker.visible = false;}
               onPositionChanged: { GL_Manager.setMouseMoveEvent(mouse.x, mouse.y);}
           }
    }

    Rectangle {
        id: buttonColorPicker
        height: (Math.max(50,root.height/20))
        width: (Math.max(50,root.height/20))
        x : (Math.max(5, root.height/100))
        y : root.height -  2 * (Math.max(50,root.height/20)) - 2 * (Math.max(5, root.height/100))
        radius : 5

        color: "grey"

        Rectangle{
            id : iconColorPicker
            anchors.fill: parent
            anchors.margins: 1
            color: "black"
            radius : iconColorPicker.width / 2

        }
        MouseArea {
               anchors.fill: parent
               onClicked:  { colorPicker.visible = !colorPicker.visible;}
        }
    }

    Rectangle{
        id: colorPicker
        visible: false
        height: (Math.max(200,root.height/5))
        width: (Math.max(200,root.height/5))
        x : 2 * Math.max(5, root.height/100) + Math.max(50,root.height/20)
        y : root.height - Math.max(200,root.height/5) - Math.max(5, root.height/100)
        color: "grey"
        radius : 5

        Image{
            id: pickerImage
            anchors.fill: parent
            anchors.margins: 1
            source: "../Images/colorPicker.png"
        }


        MouseArea {
               anchors.fill: parent
               onPressed: { Scene_Manager.setNewMainColor(mouse.x , mouse.y , pickerImage.width, pickerImage.height); iconColorPicker.color=  Scene_Manager.getMainColor(); }
               onPositionChanged: { Scene_Manager.setNewMainColor(mouse.x , mouse.y , pickerImage.width, pickerImage.height); iconColorPicker.color=  Scene_Manager.getMainColor();}
           }
    }


    Rectangle {
        height: (Math.max(50,root.height/20))
        width: (Math.max(50,root.height/20))
        x : (Math.max(5, root.height/100))
        y : root.height -   (Math.max(50,root.height/20)) -  (Math.max(5, root.height/100))
        radius : 5

        color: "grey"


        Image{
            anchors.fill: parent
            anchors.margins: 1
            source: "../Images/add.png"
        }

          MouseArea {
                anchors.fill: parent
                onClicked: {
                    GL_Manager.Open();
                }
          }


    }

    Rectangle {
        height: (Math.max(50,root.height/20))
        width: (Math.max(50,root.height/20))
        x : root.width - Math.max(50,root.height/20) -5
        y : root.height -  2* (Math.max(50,root.height/20)) - 2* (Math.max(5, root.height/100))
        radius : 5

        color: "grey"

        Image{
            anchors.fill: parent
            anchors.margins: 1
            source: "../Images/reset.png"
        }

          MouseArea {
                anchors.fill: parent
                onClicked: {
                    Scene_Manager.reset();
                }
          }
    }

    Rectangle {
        height: (Math.max(50,root.height/20))
        width: (Math.max(50,root.height/20))
        x : root.width - Math.max(50,root.height/20) -5
        y : root.height -   (Math.max(50,root.height/20)) -  (Math.max(5, root.height/100))
        radius : 5

        color: "grey"

        Image{
            anchors.fill: parent
            anchors.margins: 1
            source: "../Images/export.png"
        }

          MouseArea {
                anchors.fill: parent
                onClicked: {
                    GL_Manager.Export();
                }
          }


    }
}


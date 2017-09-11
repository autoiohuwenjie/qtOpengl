import QtQuick 2.2
//import QtQuick.Window 2.2
import OpenGLSphere 1.0

Item
{
    id: root
    width: 500
    height: 500

    Sphere
    {
        id: cube
        anchors.fill: parent
        ParallelAnimation
        {
            running: true
            NumberAnimation
            {
                target: cube
                property: "rotAngle"
                from: 0
                to: 360
                duration: 5000
            }

            Vector3dAnimation
            {
                target: cube
                property: "rotAxis"
                from: Qt.vector3d( 0, 1, 0 )
                to: Qt.vector3d( 1, 0, 0 )
                duration: 5000
            }
            loops: Animation.Infinite
        }
    }
}

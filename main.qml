import QtQuick 2.0
import QtQuick.Controls 2.2
import QtCharts 2.2
import QtQml 2.2
import qmlText 1.0

Item {
    width: 600
    height: 600
    Rectangle {
        id: testRec
        width: 600
        height: 600
        color: "red"
    }
    QmlText {
        id: myText
    }

    MouseArea {
        z: 1
        anchors.fill: parent
        onClicked: { source1.grabToImage(function(result) {
            result.saveToFile("/home/huwenjie/something.png");
            console.log(getCurrentTime());
        });
        }
    }
    Rectangle {
        id: source1
        width: 100
        height: 100
        gradient: Gradient {
            GradientStop { position: 0; color: "steelblue" }
            GradientStop { position: 1; color: "black" }
        }
    }
    function add_zero(temp)
    {
        if(temp<10) return "0"+temp;
        else return temp;
    }
    function getCurrentTime() {
        var d = new Date();
        var years = d.getFullYear();
        var month = add_zero(d.getMonth()+1);
        var days = add_zero(d.getDate());
        var hours = add_zero(d.getHours());
        var minutes = add_zero(d.getMinutes());
        var seconds=add_zero(d.getSeconds());
        var ndate = years+"-"+month+"-"+days+"-"+hours+":"+minutes+":"+seconds;
        return ndate;
    }
    Image {
        id: img2
        x: 500
        width:100
        height: 100
        Component.onCompleted: {
            console.log(getCurrentTime());
        }
    }
    Button {
        width: 50
        height: 60
        text: "保存"
        onClicked: {console.log(getCurrentTime())}
    }
}

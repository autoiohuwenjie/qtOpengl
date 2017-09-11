#include "consttest.h"
#include "htmltest.h"
#include "qmlcommunication.h"
#include "sphere.h"

#include <QDebug>
#include <QQuickView>
#include <QGuiApplication>
#include <QDir>
#include <QFile>

#include <math.h>

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    QQuickView view;
    qmlRegisterType<qmlCommunication>("qmlText", 1, 0, "QmlText");
    qmlRegisterType<Sphere>( "OpenGLSphere", 1, 0, "Sphere" );
    //view.setSource(QUrl("qrc:/DragText.qml"));
    view.setSource(QUrl("qrc:/Sphere.qml"));
    view.show();
    //    constTest mtest;
    //    qWarning() << constTest::returnNumber();
    //    HtmlTest test;
    //    test.writeDocument();
    //qWarning() << "sinValue" << sin(3.1415926 / 4.0);


    return app.exec();
}




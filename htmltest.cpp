#include "htmltest.h"
#include <QFile>

HtmlTest::HtmlTest()
{

}

void HtmlTest::writeDocument()
{
    QFile file;
    QString perfix = "/home/huwenjie/Desktop";
    file.setFileName(perfix + "/statistics/test.html");
    if (!file.exists())
    {
        file.open( QIODevice::WriteOnly);
        file.close();
    }
    file.open(QIODevice::WriteOnly);
    QString tempString = "testDocument1111";
    file.write(tempString.toLatin1());
    file.close();
}

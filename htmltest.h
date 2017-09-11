#ifndef HTMLTEST_H
#define HTMLTEST_H

#include <QFile>

#ifdef Q_OS_WIN
#define FUSION_NEW_LINE_CHAR "\r\n"
#else
#define FUSION_NEW_LINE_CHAR "\n"
#endif

class HtmlTest
{
public:
    HtmlTest();
    void writeDocument();
};

#endif // HTMLTEST_H

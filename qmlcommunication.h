#ifndef QMLCOMMUNICATION_H
#define QMLCOMMUNICATION_H

#include <QObject>

class qmlCommunication : public QObject
{
    Q_OBJECT
public:
    explicit qmlCommunication(QObject *parent = nullptr);

signals:

public slots:
    Q_INVOKABLE void writeDocument();

    Q_INVOKABLE QString getString();
};

#endif // QMLCOMMUNICATION_H

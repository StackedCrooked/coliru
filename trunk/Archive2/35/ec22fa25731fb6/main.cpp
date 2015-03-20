#include <QObject>
#include <QTimer>
#include <QDebug>


class MyClass : public QObject
{
    Q_OBJECT

public:
    MyClass()
    {
        timer = new QTimer(this);
        timer->setInterval(10);
        QObject::connect(timer, SIGNAL(timeout()), SLOT(update()));
    }

signals:
    void stateUpdated();

public slots:
    void start()
    {
        timer->start();
    }

    void stop()
    {
        timer->stop();
    }

    void update()
    {
        qDebug() << "update";
        emit stateUpdated();
    }

private:
    QTimer* timer;
};




///// main
#include <iostream>

#include <QThread>

#include <unistd.h>
#include <QApplication>
#include <QDebug>

#include "myclass.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QThread thread;
    MyClass a;
    a.moveToThread(&thread);
    thread.start();
    QMetaObject::invokeMethod(&a, "start");


    //sleep(1);

    QMetaObject::invokeMethod(&a, "stop");

    thread.exit();

    qDebug() << "before wait";
    thread.wait(); // <---- stuck
    qDebug() << "after wait";
    int ans = app.exec();
    qDebug() << "before return";

    return ans;
}
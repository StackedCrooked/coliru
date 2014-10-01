#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QDebug>
#include <QWindow>
#include <QMetaObject>

class MyWindow : public QWindow {
protected:
   virtual void mousePressEvent(QMouseEvent *) {
      if(width() == 200)
         setProperty("width", 400);
      else
         setProperty("width", 200);
   }
};

int main(int argc, char *argv[])
{
   QGuiApplication a(argc, argv);
   QQmlEngine engine;

   QQmlContext context(engine.rootContext());
   MyWindow qw;
   context.setContextObject(&qw);

   QQmlComponent component(&engine);
   component.setData("import QtQuick 2.2;"
                     "Item { "
                     "Timer { interval: 2000; running:true; repeat: true; onTriggered: { if(width == 200) width = 400; else width = 200; } }"
                     "Behavior on width { NumberAnimation { duration: 1000 } } }",
                     QUrl());
   qDebug() << component.errorString();
   component.create(&context);

   qw.show();
   return a.exec();
}

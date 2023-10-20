#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQuick>

#include "header/Snake.h"
#include "header/GameEngine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // registering enum to using in qml files
    qmlRegisterUncreatableMetaObject(
      gameengine::staticMetaObject, // meta object created by Q_NAMESPACE macro
      "my.gameengine",                // import statement (can be any string)
      1, 0,                          // major and minor version of the import
      "MovementDirection",                 // name in QML (does not have to match C++ name)
      "Error: only enums"            // error in case someone tries to create a MyNamespace object
    );

    QQuickView view;
    QQmlContext* context = view.engine()->rootContext();

    // setting our game engine to context property
    GameEngine engine;
    context->setContextProperty("_engine", &engine);

    view.setSource(QUrl("qrc:/main.qml"));

    view.show();

    engine.Start();

    return app.exec();
}

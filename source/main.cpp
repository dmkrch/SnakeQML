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

    QQuickView view;
    QQmlContext* context = view.engine()->rootContext();

    GameEngine engine;
    context->setContextProperty("_engine", &engine);

    view.setSource(QUrl("qrc:main.qml"));

    view.show();

    engine.Start();

    return app.exec();
}

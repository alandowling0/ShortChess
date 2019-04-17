#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "piecesmodel.h"
#include "highlightsmodel.h"
#include "gamecontroller.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    auto game = new Game();
    auto piecesModel = new PiecesModel(*game);
    auto highlightsModel = new HighlightsModel();
    auto gameController = new GameController(*game, *highlightsModel);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(QString("piecesModel"), piecesModel);
    engine.rootContext()->setContextProperty(QString("highlightsModel"), highlightsModel);
    engine.rootContext()->setContextProperty(QString("gameController"), gameController);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

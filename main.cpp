#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "piecesmodel.h"
#include "highlightsmodel.h"
#include "gamecontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    auto piecesModel = new PiecesModel();
    auto highlightsModel = new HighlightsModel();
    auto gameController = new GameController(*piecesModel, *highlightsModel);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(QString("piecesModel"), piecesModel);
    engine.rootContext()->setContextProperty(QString("highlightsModel"), highlightsModel);
    engine.rootContext()->setContextProperty(QString("gameController"), gameController);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

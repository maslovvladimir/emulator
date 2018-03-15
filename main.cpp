#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <iostream>
#include "server_presenter.h"
#include "device_list_model.h"
#include "device_list.h"
#include "brainbit_model.h"
#include "server/emulation_server.h"

int main(int argc, char *argv[]){

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<ServerStatePresenter>("Views", 1, 0, "ServerPresenter");
    qmlRegisterType<DeviceListModel>("DeviceList", 1, 0, "DeviceListModel");
    qmlRegisterType<BrainbitModel>("PropertyPage", 1, 0, "BrainbitModel");

    qmlRegisterUncreatableType<CallibriCommonModel>("PropertyPage", 1, 0, "CallibriCommonModel",
                                                    QStringLiteral("Callibri common should not be created in QML"));
    qmlRegisterUncreatableType<CallibriSignalModel>("PropertyPage", 1, 0, "CallibriSignalModel",
                                                    QStringLiteral("Callibri signal should not be created in QML"));
    qmlRegisterUncreatableType<PropertyPageModel>("PropertyPage", 1, 0, "PropertyPageModel",
                                                  QStringLiteral("Property page should not be created in QML"));
    qmlRegisterUncreatableType<DeviceList>("DeviceList", 1, 0, "DeviceList",
                                           QStringLiteral("Device list should not be created in QML"));

    try{
        PropertyPageModel pageModel;
        CallibriCommonModel callibriCommon;
        CallibriSignalModel callibriSignal;
        DeviceList deviceList(&pageModel, &callibriCommon, &callibriSignal,nullptr);

        if (!Net::init_sockets())
            throw std::runtime_error("Socket initialization error");
        Nes::EmulationServer server(&deviceList);

        QQmlApplicationEngine engine;
        engine.rootContext()->setContextProperty(QStringLiteral("deviceList"), &deviceList);
        engine.rootContext()->setContextProperty(QStringLiteral("propertyPageModel"), &pageModel);
        engine.rootContext()->setContextProperty(QStringLiteral("callibriCommon"), &callibriCommon);
        engine.rootContext()->setContextProperty(QStringLiteral("callibriSignal"), &callibriSignal);
        engine.load(QUrl(QLatin1String("qrc:/main.qml")));

        return app.exec();
    }
    catch (std::runtime_error& error){
        std::cerr<<error.what()<<std::endl;
        qDebug()<<error.what();
        return -1;
    }
}

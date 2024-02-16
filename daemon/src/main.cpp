#include <QDBusConnection>
#include "daemon.h"
#include "register_adaptor.h"

namespace {
    const auto DBUS_SERVICE_NAME = "ru.innop.OpenWith";
    const auto DBUS_OBJECT_PATH = "/Daemon";
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    auto daemon = new ow::Daemon();

    new RegisterInterfaceAdaptor(daemon);
    auto connection = QDBusConnection::sessionBus();
    connection.registerObject(DBUS_OBJECT_PATH, daemon);
    connection.registerService(DBUS_SERVICE_NAME);
    app.exec();
    return 0;
}

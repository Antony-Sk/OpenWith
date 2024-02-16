//
// Created by anton on 16.02.24.
//

#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusInterface>
#include <iostream>
#include <filesystem>

namespace {
    const auto DBUS_SERVICE = "ru.innop.OpenWith";
    const auto DBUS_PATH = "/Daemon";
    const auto DBUS_METHOD = "open";
}

/* This executable just expect first argument to be a file to open, then send dbus message to daemon which stores
 * all handlers
 */
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Expected file to open";
        return -1;
    }
    auto connection = QDBusConnection::sessionBus();
    if (!connection.isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n");
        return 1;
    }

    QDBusInterface iface(DBUS_SERVICE, DBUS_PATH);
    if (iface.isValid()) {
        std::string path = std::filesystem::current_path();
        path += "/";
        path += argv[1];
        QDBusReply<void> reply = iface.call(DBUS_METHOD, QString(path.c_str()));
        if (reply.isValid()) {
            std::cout << "Signal to daemon is sent";
            return 0;
        }

        qWarning("Call failed: %s\n", qPrintable(reply.error().message()));
        return 1;
    }

    qWarning("%s\n", qPrintable(connection.lastError().message()));
}
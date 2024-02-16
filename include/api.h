//
// Created by anton on 15.02.24.
//

#ifndef OMPTESTTASK_API_H
#define OMPTESTTASK_API_H

#include <string>
#include <QtDBus>
#include <iostream>

namespace {
    const auto DBUS_SERVICE = "ru.innop.OpenWith";
    const auto DBUS_PATH = "/Daemon";
    const auto DBUS_METHOD = "reg_format";
}
namespace ow {
    /*
     * @Returns: void
     * @Params:
     * - format: extension of the file (e.g. "txt", "pdf", "png" ...)
     * - exec_path: path of executable handler (e.g. "/bin/bash", "/bin/cat" ...)
     * - exec_args: arguments to pass to handler (e.g. "-c", "--file")
     * The function creates register handler in OpenWith daemon via dbus and passes ot it its args
     * When someone wants to open the file (e.g. a.txt) daemon determines its ext and creates an instance of handler
     * (e.g. "/bin/cat a.txt ", "texteditor --file a.txt")
     * */
    static void register_handler(const std::string &format, const std::string &exec_path,
                                 const std::initializer_list<std::string> &exec_args) {
        auto connection = QDBusConnection::sessionBus();

        if (!connection.isConnected()) {
            qWarning("Cannot connect to the D-Bus session bus.\n"
                     "To start it, run:\n"
                     "\teval `dbus-launch --auto-syntax`\n");
            exit(1);
        }
        QDBusInterface iface(DBUS_SERVICE, DBUS_PATH);
        if (iface.isValid()) {
            auto args = QStringList();
            args.reserve(exec_args.size());
            for (const auto &arg: exec_args)
                args.push_back(arg.c_str());
            QDBusReply<void> reply = iface.call(DBUS_METHOD, format.c_str(), exec_path.c_str(), args);
            if (reply.isValid()) {
                std::cout << "Handler registered";
                return;
            }

            qWarning("Call failed: %s\n", qPrintable(reply.error().message()));
            exit(1);
        }

        qWarning("%s\n", qPrintable(connection.lastError().message()));
    }
}

#endif //OMPTESTTASK_API_H

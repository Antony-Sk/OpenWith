//
// Created by anton on 16.02.24.
//

#include <iostream>
#include "daemon.h"

void ow::Daemon::reg_format(const QString &format, const QString &exec_path, const QStringList &exec_args) {
    handlers[format] = {exec_path, exec_args};

    storage.open(STORAGE_FILE_NAME, std::fstream::out);
    for (const auto &arg: exec_args)
        storage << arg.toStdString() << " ";
    storage << format.toStdString() << " " << exec_path.toStdString() << "\n";
    storage.close();

    std::cerr << "New handler for '" << format.toStdString() << "' with exec '" << exec_path.toStdString();
    for (const auto &arg: exec_args)
        std::cerr << " " << arg.toStdString();
    std::cerr << "'\n";
}

ow::Daemon::Daemon() {
    storage.open(STORAGE_FILE_NAME, std::fstream::in);
    for (std::string line; std::getline(storage, line);) {
        auto words = QString(line.c_str()).split(" ");
        auto exec_path = words.back();
        words.pop_back();
        auto format = words.back();
        words.pop_back();
        handlers[format] = {exec_path, words};
    }
    storage.close();
};

ow::Daemon::~Daemon() = default;

void ow::Daemon::open(const QString &file) {
    auto ext = file.split(".").last();
    if (handlers.contains(ext)) {
        std::string args;
        for (const auto &arg: handlers[ext].second)
            args += arg.toStdString() + " ";
        std::cerr << "Executing '" << handlers[ext].first.toStdString() << " " << args << file.toStdString() << "'\n";
        std::cerr.flush();
        std::cout.flush();
        if (!fork()) {
            execl(handlers[ext].first.toStdString().c_str(), args.c_str(), file.toStdString().c_str(),
                  (char *) nullptr);
        }
    } else {
        std::cerr << "No handlers found for '" << ext.toStdString() << "'\n";
    }
}

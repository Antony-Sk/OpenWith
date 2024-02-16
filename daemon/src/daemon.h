//
// Created by anton on 16.02.24.
//

#ifndef OMPTESTTASK_DAEMON_H
#define OMPTESTTASK_DAEMON_H

#include <QtCore>
#include <fstream>

namespace ow {
    class Daemon : public QObject {
    private:
        // Handlers: extension -> {exec_path, exec_params}
        std::unordered_map<QString, std::pair<QString, QStringList>> handlers;

        const std::string STORAGE_FILE_NAME = "handlers.txt";
        std::fstream storage;
    Q_OBJECT

    public:
        Daemon();

        virtual ~Daemon();

    public slots:

        void reg_format(const QString& format, const QString& exec_path, const QStringList& exec_args);

        void open(const QString& format);
    };
}


#endif //OMPTESTTASK_DAEMON_H

//
// Created by Dev on 08/12/2024.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include "Message.h"


namespace TerminalColors {
    const std::string HEADER = "\033[95m";
    const std::string OKBLUE = "\033[94m";
    const std::string OKCYAN = "\033[96m";
    const std::string OKGREEN = "\033[92m";
    const std::string WARNING = "\033[93m";
    const std::string FAIL = "\033[91m";
    const std::string ENDC = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string UNDERLINE = "\033[4m";
}

class Logger {
    std::vector<Message> _messages;
    Logger() = default;

public:
    static Logger& getInstance();
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator= (const Logger&) = delete;

    void log(const Message& message);
    void debug(const std::string& sender, const std::string& message);
    void info(const std::string& sender, const std::string& message);
    void warn(const std::string& sender, const std::string& message);
    void error(const std::string& sender, const std::string& message);
};



#endif //LOGGER_H

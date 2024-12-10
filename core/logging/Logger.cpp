//
// Created by Dev on 08/12/2024.
//

#include "Logger.h"
#include <iostream>
#include <sstream>
#include <ctime>

Logger & Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::log(const Message &message) {
    time_t tt;
    time(&tt);
    const tm *ti = localtime(&tt);
    std::string time = asctime(ti);
    time.pop_back();
    std::cout << "(" << time << ")" << std::endl;

    _messages.push_back(message);
    switch (message.getType()) {
        case MESSAGE_TYPE_UNKNOWN:
            std::cout << TerminalColors::UNDERLINE;
            break;
        case MESSAGE_TYPE_ERROR:
            std::cout << TerminalColors::FAIL << TerminalColors::BOLD;
            break;
        case MESSAGE_TYPE_WARNING:
            std::cout << TerminalColors::WARNING << TerminalColors::BOLD;
            break;
        case MESSAGE_TYPE_INFO:
            break;
        case MESSAGE_TYPE_DEBUG:
            std::cout << TerminalColors::OKBLUE;
            break;
        default:
            std::cerr << "Unknown message type: " << message.getType() << std::endl;
    }

    std::cout << "[" << message.getSender() << "] " << message.getMessage();
    std::cout << TerminalColors::ENDC << std::endl;
}

void Logger::debug(const std::string &sender, const std::string &message) {
    Message msg;
    msg.setType(MESSAGE_TYPE_DEBUG);
    msg.setSender(sender);
    msg.setMessage(message);
    _messages.push_back(msg);
    log(msg);
}

void Logger::info(const std::string &sender, const std::string &message) {
    Message msg;
    msg.setType(MESSAGE_TYPE_INFO);
    msg.setSender(sender);
    msg.setMessage(message);
    _messages.push_back(msg);
    log(msg);
}

void Logger::warn(const std::string &sender, const std::string &message) {
    Message msg;
    msg.setType(MESSAGE_TYPE_WARNING);
    msg.setSender(sender);
    msg.setMessage(message);
    _messages.push_back(msg);
    log(msg);
    std::stringstream ss;
    ss << "[" << sender << "] " << message;
    throw std::runtime_error(ss.str());
}

void Logger::error(const std::string &sender, const std::string &message) {
    Message msg;
    msg.setType(MESSAGE_TYPE_ERROR);
    msg.setSender(sender);
    msg.setMessage(message);
    _messages.push_back(msg);
    log(msg);
    std::stringstream ss;
    ss << "[" << sender << "] " << message;
    throw std::runtime_error(ss.str());
}



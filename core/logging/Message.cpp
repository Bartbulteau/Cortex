//
// Created by Dev on 08/12/2024.
//

#include "Message.h"

void Message::setSender(const std::string &sender) {
    _sender = sender;
}

void Message::setType(const MessageType &type) {
    _type = type;
}

void Message::setMessage(const std::string &message) {
    _message = message;
}

const std::string & Message::getMessage() const {
    return _message;
}

const std::string & Message::getSender() const {
    return _sender;
}

MessageType Message::getType() const {
    return _type;
}

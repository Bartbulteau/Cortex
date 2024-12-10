//
// Created by Dev on 08/12/2024.
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

typedef enum MessageType {
    MESSAGE_TYPE_UNKNOWN = 0,
    MESSAGE_TYPE_ERROR = 1,
    MESSAGE_TYPE_WARNING = 2,
    MESSAGE_TYPE_INFO = 3,
    MESSAGE_TYPE_DEBUG = 4
} MessageType;

class Message {
    std::string _message;
    std::string _sender;
    MessageType _type = MESSAGE_TYPE_UNKNOWN;

public:
    Message() = default;
    Message(const Message& other) = default;
    ~Message() = default;

    Message& operator=(const Message& other) = default;

    void setSender(const std::string& sender);
    void setType(const MessageType& type);
    void setMessage(const std::string& message);

    const std::string& getMessage() const;
    const std::string& getSender() const;
    MessageType getType() const;
};



#endif //MESSAGE_H

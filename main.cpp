#include <iostream>
#include "json/json.h"
#include "serial/serial.h"
#include "logger.hpp"

int main() {
    // json check
    Json::Value root;
    root["name"] = "Daniil";

    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, root);

    std::cout << json_file << std::endl;

    std::cout << "----------------------------------" << std::endl;
    // serial check

    serial::Serial serial_port("/dev/ttyUSB0", 115200, serial::Timeout::simpleTimeout(1000));

    if (serial_port.isOpen()) {
        std::cout << "Port is opened..." << std::endl;
    }
    else {
        std::cout << "Failed to open port..." << std::endl;
        return -1;
    }

    std::string msg_send("hello!");
    size_t bytes_sent = serial_port.write(msg_send);
    std::cout << std::to_string(bytes_sent) + " bytes sent..." << std::endl;

    if (serial_port.waitReadable()) {
        std::string result = serial_port.read(msg_send.length());
        std::cout << "Received: " + result << std::endl;
    }
    else {
        std::cout << "Timeout, failed to recieve...";
        return -1;
    }

    return 0;
}
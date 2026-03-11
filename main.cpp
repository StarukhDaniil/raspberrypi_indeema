#include <iostream>
#include "json/json.h"
#include "serial/serial.h"
#include "logger.hpp"
#include "jsonparser.hpp"
#include "serial_listener.hpp"

int main() {
    serial::Serial serial_port("/dev/ttyUSB0", 115200, serial::Timeout::simpleTimeout(5000));
    TSafeContainer<std::queue<std::string>> tsc(std::make_shared<std::queue<std::string>>(),
        std::make_shared<std::condition_variable_any>(),
        std::make_shared<std::shared_mutex>(),
        []() { return true; });
    JsonParser parser(tsc);
    SerialListener listener(tsc);

    std::unique_ptr<std::jthread> logger_thread = parser.start_event_loop();
    std::unique_ptr<std::jthread> listener_thread = listener.start_event_loop(&serial_port);

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    std::string msg_send("{\"path\": \"/dev/ttyUSB0\",\"baud_rate\": 115200 }\n");
    size_t bytes_sent = serial_port.write(msg_send);
    return 0;
}
#include "serial_listener.hpp"
#include <serial/serial.h>
#include <iostream>

void SerialListener::event_loop(serial::Serial* port) {
    std::unique_lock<std::shared_mutex> lock(*m_queue.mtx().get(), std::defer_lock);
    std::shared_ptr<std::queue<std::string>> pqueue(m_queue.container());
    std::string received_str;

    if (!port->isOpen()) {
        throw std::runtime_error("Failed to open port...");
    }

    while(true) {
        if(port->waitReadable()) {
            received_str = port->readline();
            std::cout << "[serial_listener]: received!" << std::endl;
            lock.lock();
            std::cout << "[serial_listener]: mutex locked" << std::endl;
            pqueue.get()->push(received_str);
            lock.unlock();
            std::cout << "[serial_listener]: mutex unlocked" << std::endl;
        }
        else {
            std::cout << "[serial_listener]: no data received for 5 seconds..." << std::endl;
        }
    }
}

std::unique_ptr<std::jthread> SerialListener::start_event_loop(serial::Serial* port) {
    std::unique_ptr<std::jthread> pthread = std::make_unique<std::jthread>(&SerialListener::event_loop, this, port);
    return std::move(pthread);
}

SerialListener::SerialListener(const TSafeContainer<std::queue<std::string>>& ts_container)
    : m_queue(ts_container) {

}
SerialListener::SerialListener(const std::shared_ptr<std::queue<std::string>>& container,
           const std::shared_ptr<std::condition_variable_any>& cv,
           const std::shared_ptr<std::shared_mutex>& mtx,
           const std::function<bool(void)> cv_check) 
    : m_queue(container, cv, mtx, cv_check){
}
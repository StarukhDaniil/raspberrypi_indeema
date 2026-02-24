#pragma once

#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include "serial/serial.h"
#include "tsafecontainer.hpp"

class SerialListener {
private:
    TSafeContainer<std::queue<std::string>> m_queue;
public:
    std::unique_ptr<std::jthread> start_event_loop(serial::Serial* port);

    SerialListener(const TSafeContainer<std::queue<std::string>>& ts_container);
    SerialListener(const std::shared_ptr<std::queue<std::string>>& container,
                   const std::shared_ptr<std::condition_variable_any>& cv,
                   const std::shared_ptr<std::shared_mutex>& mtx,
                   const std::function<bool(void)> cv_check);
private:
    void event_loop(serial::Serial* port);
};
#pragma once

#include "json/json.h"
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include "tsafecontainer.hpp"

struct DevInfo;

class JsonParser {
private:
    TSafeContainer<std::queue<std::string>> m_queue;
public:
    const TSafeContainer<std::queue<std::string>>& queue() const;    
    TSafeContainer<std::queue<std::string>>& queue();

    DevInfo parseFile(const std::string& path);
    Json::Value parseString(const std::string& json) const;
    std::unique_ptr<std::jthread> start_event_loop();

    JsonParser(const TSafeContainer<std::queue<std::string>>& ts_container);
    JsonParser(const std::shared_ptr<std::queue<std::string>>& container,
               const std::shared_ptr<std::condition_variable_any>& cv,
               const std::shared_ptr<std::shared_mutex>& mtx,
               const std::function<bool(void)> cv_check);
private:
    void event_loop();
};

struct DevInfo {
private:
    std::string m_path;
    uint32_t m_baud_rate;
public:
    std::string& path();
    uint32_t& baud_rate();

    const std::string& path() const;
    uint32_t baud_rate() const;
};
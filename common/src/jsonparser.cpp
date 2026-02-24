#include "jsonparser.hpp"
#include <fstream>
#include <iostream>

DevInfo JsonParser::parseFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file for reading");
    }

    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;

    if (!Json::parseFromStream(builder, file, &root, &errs)) {
        throw std::runtime_error("error while parsing");
    }

    if (!root.isMember("path")) {
        throw std::runtime_error("json doesn't have \"path\" field");
    }
    else if (!root.isMember("baud_rate")) {
        throw std::runtime_error("json doesn't have \"baud_rate\" field");
    }

    DevInfo info;
    info.path() = root["path"].asString();
    info.baud_rate() = root["baud_rate"].asUInt64();

    return info;
}

Json::Value JsonParser::parseString(const std::string& json) const {
    Json::Value root;
    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    std::string errs;

    bool success = reader->parse(json.c_str(), json.c_str() + json.size(), &root, &errs);
    if (!success) {
        throw std::runtime_error("error while parsing json string: " + errs);
    }

    return root;
}

const std::string& DevInfo::path() const {
    return m_path;
}

uint32_t DevInfo::baud_rate() const {
    return m_baud_rate;
}

const TSafeContainer<std::queue<std::string>>& JsonParser::queue() const {
    return m_queue;
}
    
TSafeContainer<std::queue<std::string>>& JsonParser::queue() {
    return m_queue;
}

std::string& DevInfo::path() {
    return m_path;
}
uint32_t& DevInfo::baud_rate() {
    return m_baud_rate;
}


void JsonParser::event_loop() {
    std::unique_lock<std::shared_mutex> lock(*m_queue.mtx().get(), std::defer_lock);
    std::shared_ptr<std::queue<std::string>> pcontainer = m_queue.container();
    std::shared_ptr<std::condition_variable_any> pcv = m_queue.cv();

    while(true) {
        pcv.get()->wait(lock, m_queue.cv_check_func());

        while(!pcontainer.get()->empty()) {
            std::string json_str = pcontainer.get()->front();
            pcontainer.get()->pop();
            
            Json::Value parsed = parseString(json_str);
            std::cout << parsed << std::endl;;
        }
    }
}

std::unique_ptr<std::jthread> JsonParser::start_event_loop() {
    std::unique_ptr<std::jthread> pthread = std::make_unique<std::jthread>(&JsonParser::event_loop, this);
    return std::move(pthread);
}

JsonParser::JsonParser(const TSafeContainer<std::queue<std::string>>& ts_container)
    : m_queue(ts_container) {

}
JsonParser::JsonParser(const std::shared_ptr<std::queue<std::string>>& container,
           const std::shared_ptr<std::condition_variable_any>& cv,
           const std::shared_ptr<std::shared_mutex>& mtx,
           const std::function<bool(void)> cv_check) 
    : m_queue(container, cv, mtx, cv_check){
}
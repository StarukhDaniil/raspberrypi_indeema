#include "jsonparser.hpp"
#include <fstream>

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

    DevInfo info(root["path"].asString(), root["baud_rate"].asUInt64());

    return info;
}

DevInfo::DevInfo(const DevInfo& other) {
    if (&other == this) {
        return;
    }

    this->m_baud_rate = other.baud_rate();
    this->m_path = other.path();
}

DevInfo::DevInfo(const std::string& path, uint32_t baud_rate) {
    this->m_path = path;
    this->m_baud_rate = baud_rate;
}

const std::string& DevInfo::path() const {
    return m_path;
}

uint32_t DevInfo::baud_rate() const {
    return m_baud_rate;
}
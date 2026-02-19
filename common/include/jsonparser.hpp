#pragma once

#include "json/json.h"
#include <string>

struct DevInfo;

class JsonParser {
private:

public:
    DevInfo parseFile(const std::string& path);
};

struct DevInfo {
private:
    std::string m_path;
    uint32_t m_baud_rate;
public:
    DevInfo(const DevInfo& other);
    DevInfo(const std::string& path, uint32_t baud_rate);
    const std::string& path() const;
    uint32_t baud_rate() const;
};
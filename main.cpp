#include <iostream>
#include "json/json.h"
#include "logger.hpp"

int main() {
    Json::Value root;
    root["name"] = "Daniil";

    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, root);

    std::cout << json_file << std::endl;

    return 0;
}
#include <iostream>
#include "json/json.h"
#include "serial/serial.h"
#include "logger.hpp"
#include "jsonparser.hpp"

int main() {
    JsonParser parser;
    std::string file_path;

    std::cin >> file_path;
    DevInfo info(parser.parseFile(file_path));

    std::cout << "path: " << info.path() << std::endl;
    std::cout << "baud_rate: " << std::to_string(info.baud_rate()) << std::endl;
    return 0;
}
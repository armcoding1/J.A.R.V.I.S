#include <functional>
#include <iostream>
#include <unordered_map>
#include "executor.h"

namespace executor {
void execute(const std::string &command) {
    static std::unordered_map<std::string, std::function<void()>> commands = {
        {"hello", []() { std::cout << "Hello, Armen!" << std::endl; }},
        {"exit", []() {std::cout << "Exit..." << std::endl; exit(0); }}};

    if (commands.find(command) != commands.end()) {
        commands[command]();
    } else {
        std::cout << "Unknown Command: " << command << std::endl;
    }
}
}
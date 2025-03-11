#include <string>
#include <iostream>
#include "command_parser.h"
#include "executor.h"

int main() {
    std::string input;

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        std::string parsed_command = command_parser::parse_command(input);
        executor::execute(parsed_command);
    }

    return 0;
}
#include <iostream>
#include <fmt/core.h>
#include <fstream>  
#include <string>
#include "cplox.hpp"
#include "scanner.hpp"

#define VERSION "0.0.1"

namespace Cplox {

void run(const std::string& source) {
    Scanner scanner{source};
    std::vector<Token> tokens = scanner.scanTokens();

    // for (Token token : tokens) {
    //     fmt::print(token.toString());
    // }
}

void runFile(const std::string& file_name) {
    std::ifstream file(file_name);

    if (!file.good()) {
        fmt::print("Failed. {} does not exist", file_name);
    }

    std::string bytes = "";
    std::string line;
    while (std::getline(file, line)) {
        bytes += line + "\n";
    }

    run(bytes);
    if (Cplox::hadError) exit(1);
}

[[noreturn]] void runPrompt() {

    fmt::print("cplox v{}\n", VERSION);

    std::string line;
    while (true) {
        fmt::print(">");
        if (std::getline(std::cin, line)) {
            run(line);
            Cplox::hadError = false;
        } else {
            fmt::print("\n");
            break;
        }
    }
}

}

int main(int args, char* argv[]) {
    if (args > 2) {
        fmt::print("Usage cplox [script]\n");
        exit(1);
    } else if (args == 2) {
        Cplox::runFile(argv[1]);
    } else {
        Cplox::runPrompt();
    }
}
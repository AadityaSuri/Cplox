#include "cplox.hpp"
#include <fmt/core.h>

namespace Cplox {

bool Cplox::hadError = false;

void Cplox::report(int line, const std::string& where, const std::string& message) {
    fmt::print("[line {}], Error{}: {}\n", line, where, message);
    hadError = true;
}

void Cplox::error(int line, const std::string& message) {
    report(line, "", message);
}

}
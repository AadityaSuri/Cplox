#pragma once

#include <string>

namespace Cplox {

class Cplox {
    static void report(int line, const std::string& where, const std::string& message);   

public:
    static bool hadError;
    static void error(int line, const std::string& message);

};

}
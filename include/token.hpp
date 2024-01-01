#pragma once

#include <string>
#include <any>
#include "tokenType.hpp"

namespace Cplox
{

class Token {
    const TokenType type;
    const std::string lexeme;
    const std::any literal;
    const int line; 

    public:
    Token(TokenType type, std::string lexeme, std::any literal, int line);

    [[maybe_unused]] std::string toString();

    TokenType getType();
    std::string getLexeme();
    std::any getLiteral();
    int getLine();
};

} // namespace Cplox

#pragma once

#include "token.hpp"
#include "tokenType.hpp"
#include <string>
#include <vector>
#include <any>
#include <unordered_map>
#include "tokenType.hpp"

namespace Cplox {

class Scanner {
    const std::string source;
    std::vector<Token> tokens;
    int start{0}, current{0}, line{1};

    std::unordered_map<std::string, TokenType> keywords = 
    {
        {"and", AND},
        {"class", CLASS},
        {"else", ELSE},
        {"false", FALSE},
        {"fn", FN},
        {"for", FOR},
        {"if", IF},
        {"nil", NIL},
        {"or", OR},
        {"print", PRINT},
        {"return", RETURN},
        {"super", SUPER},
        {"this", THIS},
        {"true", TRUE},
        {"var", VAR},
        {"while", WHILE}
    };

    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, std::any literal);
    bool match(char expected);
    char peek();
    char peekNext();
    void string();
    void number();
    void identifer();

    static std::string substring(const std::string& str, int start, int current);

    public:
    Scanner(const std::string& source);
    std::vector<Token> scanTokens();
};

}
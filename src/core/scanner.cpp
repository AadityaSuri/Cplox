#include "token.hpp"
#include "tokenType.hpp"
#include "scanner.hpp"
#include "cplox.hpp"

#include <fmt/core.h>

namespace Cplox{

Scanner::Scanner(const std::string& source) : source(source) {};

std::vector<Token> Scanner::scanTokens() {
    
    while (!isAtEnd()) {
        // beginning of next lexeme
        start = current;
        scanToken();
    }

    tokens.push_back(Token{tokenEOF, "", NULL, line});
    return tokens;
}

void Scanner::scanToken() {
    char c = advance();
    
    switch (c) {
    case '(': addToken(LEFT_PARAN); break;
    case ')': addToken(RIGHT_PARAN); break;
    case '{': addToken(LEFT_BRACE); break;
    case '}': addToken(RIGHT_BRACE); break;
    case ',': addToken(COMMA); break;
    case '.': addToken(DOT); break;
    case '-': addToken(MINUS); break;
    case '+': addToken(PLUS); break;
    case ';': addToken(SEMICOLON); break;
    case '*': addToken(STAR); break;

    case '!': 
        addToken(match('=') ? NOT_EQUAL : NOT);
        break;

    case '=':
        addToken(match('=') ? EQUAL_EQUAL : EQUAL);
        break;

    case '>':
        addToken(match('=') ? GREATER_EQUAL : GREATER);
        break;

    case '<':
        addToken(match('=') ? LESS_EQUAL : LESS);
        break;

    case '/':
        if (match('/')) {
            while (peek() != '\n' && !isAtEnd()) { advance(); }
        } else {
            addToken(SLASH);
        }
        break;

    case ' ':
    case '\r':
    case '\t':
        break;
    
    case '\n':
        line++;
        break;

    case '"':
        string();
        break;

    default:
        if (isdigit(c)) {
            number();
        } else if(isalpha(c)) {
            identifer();
        } else {
            Cplox::error(line, fmt::format("Unexpected character \"{}\" ", c)); break;
        }
    }
}

char Scanner::advance() {
    return source[current++];
}

void Scanner::addToken(TokenType type) {
    addToken(type, NULL);
}

void Scanner::addToken(TokenType type, std::any literal) {
    std::string text = substring(source, start, current);
    tokens.push_back(Token{type, text, literal, line});
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') { line++; }
        advance();
    }

    if (isAtEnd()) {
        Cplox::error(line, "Unterminated string.");
    }

    advance();

    // strip off the quotation marks
    std::string value = substring(source, start + 1, current - 1);
    addToken(STRING, value);
}

void Scanner::number() {

    while (isdigit(peek())) { advance(); }

    if (peek() == '.' && isdigit(peekNext())) {
        advance();

        while (isdigit(peek())) advance();
    }

    addToken(NUMBER, stod(substring(source, start, current)));
}

void Scanner::identifer() {
    
    while (isalnum(peek())) { advance(); }

    std::string text = substring(source, start, current);
    
    if (keywords.contains(text)) {
        addToken(keywords[text]);
    } else {
        addToken(IDENTIFER);
    }
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;

    if (source[current] != expected) return false;

    current++;
    return true;

}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Scanner::peekNext() {
    if (current + 1 > source.length()) return '\0';
    return source[current + 1]; 
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

std::string Scanner::substring(const std::string& str, int start_, int current_) {
    return str.substr(start_, current_ - start_);
}

}
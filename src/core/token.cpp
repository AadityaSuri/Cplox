#include "token.hpp"
#include <fmt/core.h>

namespace Cplox
{

Token::Token(TokenType type, std::string lexeme, std::any literal, int line):
    type(type),
    lexeme(lexeme),
    literal(literal),
    line(line)
{}

[[maybe_unused]] std::string Token::toString() {
    return fmt::format("{} {} {}\n", static_cast<int>(type), lexeme, "_");
}
TokenType Token::getType() { return type; }
std::string Token::getLexeme() { return lexeme; }
std::any Token::getLiteral() { return literal; }
int Token::getLine() { return line; }

} // namespace Cplox

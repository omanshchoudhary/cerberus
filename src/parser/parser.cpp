#include "../../include/parser/parser.h"

Parser::Parser(const std::vector<Token>& tokens): tokens(tokens) {}

bool Parser::isAtEnd() const {
    return tokens[current].type==TokenType::EOF_TOKEN;
}

const Token& Parser::peek() const {
    return tokens[current];
}

const Token& Parser::previous() const {
    return tokens[current-1];
}

const Token& Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}
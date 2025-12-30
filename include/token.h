#pragma once

#include<string>

enum class TokenType {
    LET,
    PRINT,
    IF,
    ELSE,
    WHILE,

    IDENTIFIER,
    NUMBER,

    PLUS,
    MINUS,
    STAR,
    EQUAL,
    EQUAL_EQUAL,
    LESS,
    GREATER,

    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    SEMICOLON,

    EOF_TOKEN

};

struct Token{
    TokenType type;
    std::string lexeme;
    int line;
};
#include<bits/stdc++.h>
using namespace std;

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
    string lexeme;
    int line;
};
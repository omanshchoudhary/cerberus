#pragma once

#include <vector>
#include "../token.h"
#include "../ast/expr.h"
#include "../ast/stmt.h"

class Parser
{
public:
    explicit Parser(const std::vector<Token> &tokens);
    Stmt* parseStatement();

private:
    const std::vector<Token> &tokens;
    int current = 0;
    bool isAtEnd() const;
    const Token& peek() const;
    const Token& previous() const;
    const Token& advance();
    bool check(TokenType type) const;
    bool match(TokenType type);
    Expr* expression();
    Expr* term();
    Expr* factor();
    Stmt* letStatement();
    Stmt* printStatement();

};
#pragma once
#include<string>
#include "../token.h"

struct Expr{
    virtual ~Expr()=default;
};

struct LiteralExpr : Expr {
    int value;

    LiteralExpr(int value) : value(value) {}
};

struct VariableExpr : Expr {
    std::string name;

    VariableExpr(std::string name) : name(name) {}
};

struct BinaryExpr : Expr {
    Expr* left;

    TokenType op;

    Expr* right;

    BinaryExpr(Expr* left, TokenType op, Expr* right): left(left), op(op), right(right) {}
};

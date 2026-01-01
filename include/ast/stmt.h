#pragma once
#include<string>
#include "expr.h"

struct Stmt {
    virtual ~Stmt() = default;
};

struct LetStmt : Stmt {
    std::string name;
    Expr* initializer;

    LetStmt(const std::string& name, Expr* initializer) : name(name), initializer(initializer) {}
};

struct PrintStmt : Stmt {
    Expr* expression;
    
    explicit PrintStmt(Expr* expression) : expression(expression){}
};
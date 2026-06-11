#pragma once
#include<string>
#include<vector>
#include "expr.h"

struct Stmt
{
    virtual ~Stmt() = default;
};

struct LetStmt : Stmt
{
    std::string name;
    Expr *initializer;

    LetStmt(const std::string &name, Expr *initializer) : name(name), initializer(initializer) {}
};

struct PrintStmt : Stmt
{
    Expr *expression;

    explicit PrintStmt(Expr *expression) : expression(expression) {}
};

struct BlockStmt : Stmt
{
    std::vector<Stmt *> statements;
};

struct IfStmt : Stmt
{
    Expr *condition;
    Stmt *thenBranch;
    Stmt *elseBranch;
};

struct WhileStmt : Stmt
{
    Expr *condition;
    Stmt *body;
};

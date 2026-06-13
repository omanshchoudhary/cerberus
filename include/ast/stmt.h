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

    explicit BlockStmt(std::vector<Stmt *> statements) : statements(statements) {}
};

struct IfStmt : Stmt
{
    Expr *condition;
    Stmt *thenBranch;
    Stmt *elseBranch;

    IfStmt(Expr *condition, Stmt *thenBranch, Stmt *elseBranch)
        : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}
};

struct WhileStmt : Stmt
{
    Expr *condition;
    Stmt *body;

    WhileStmt(Expr *condition, Stmt *body) : condition(condition), body(body) {}
};

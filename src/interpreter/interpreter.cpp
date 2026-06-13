#include <stdexcept>
#include "../../include/interpreter/interpreter.h"
#include "../../include/interpreter/environment.h"
#include "../../include/token.h"
#include <iostream>

static Environment globalEnv;
static Environment *currentEnv = &globalEnv;

void defineVariable(const std::string &name, int value)
{
    currentEnv->define(name, value);
}

void assignVariable(const std::string &name, int value)
{
    currentEnv->assign(name, value);
}

int evaluate(Expr *expr)
{
    if (auto *literal = dynamic_cast<LiteralExpr *>(expr))
    {
        return literal->value;
    }
    if (auto *binary = dynamic_cast<BinaryExpr *>(expr))
    {
        int left = evaluate(binary->left);
        int right = evaluate(binary->right);

        switch (binary->op)
        {
        case TokenType::PLUS:
            return left + right;
        case TokenType::MINUS:
            return left - right;
        case TokenType::STAR:
            return left * right;
        case TokenType::SLASH:
            return left / right;
        case TokenType::LESS:
            return left < right;
        case TokenType::GREATER:
            return left > right;
        case TokenType::EQUAL_EQUAL:
            return left == right;
        default:
            throw std::runtime_error("Unsupported binary operator");
        }
    }
    if (auto *variable = dynamic_cast<VariableExpr *>(expr))
    {
        return currentEnv->get(variable->name);
    }
    throw std::runtime_error("Unknown expression type");
}

void execute(Stmt *stmt)
{
    if (auto *letStmt = dynamic_cast<LetStmt *>(stmt))
    {
        int value = evaluate(letStmt->initializer);
        defineVariable(letStmt->name, value);
        return;
    }
    if (auto *printStmt = dynamic_cast<PrintStmt *>(stmt))
    {
        int value = evaluate(printStmt->expression);
        std::cout << value << std::endl;
        return;
    }
    if (auto *blockStmt = dynamic_cast<BlockStmt *>(stmt))
    {
        Environment *previous = currentEnv;
        Environment blockEnv(previous);
        currentEnv = &blockEnv;
        for (Stmt *statement : blockStmt->statements)
        {
            execute(statement);
        }
        currentEnv = previous;
        return;
    }
    if (auto *ifStmt = dynamic_cast<IfStmt *>(stmt))
    {
        if (evaluate(ifStmt->condition))
        {
            execute(ifStmt->thenBranch);
        }
        else if (ifStmt->elseBranch != nullptr)
        {
            execute(ifStmt->elseBranch);
        }
        return;
    }
    if (auto *whileStmt = dynamic_cast<WhileStmt *>(stmt))
    {
        while (evaluate(whileStmt->condition))
        {
            execute(whileStmt->body);
        }
        return;
    }

    if (auto *assignStmt = dynamic_cast<AssignStmt *>(stmt))
    {
        assignVariable(assignStmt->name, evaluate(assignStmt->value));
        return;
    }
    


    throw std::runtime_error("Unknown statement type");
}


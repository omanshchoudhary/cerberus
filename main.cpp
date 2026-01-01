#include <iostream>
#include "include/ast/expr.h"
#include "include/token.h"
#include "include/interpreter/interpreter.h"

int main() {
    defineVariable("x", 5);
    Expr* expr = new BinaryExpr(
        new VariableExpr("x"),
        TokenType::PLUS,
        new LiteralExpr(3)
    );
    std::cout <<evaluate(expr);
    return 0;
}

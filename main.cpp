#include <iostream>
#include "./include/ast/expr.h"
#include "./include/token.h"
#include "./include/interpreter/interpreter.h"

int main() {
    Expr* expr = new BinaryExpr(
        new LiteralExpr(10),
        TokenType::PLUS,
        new BinaryExpr(
            new LiteralExpr(2),
            TokenType::STAR,
            new LiteralExpr(3)
        )
    );
    std::cout<<evaluate(expr);
    return 0;
}

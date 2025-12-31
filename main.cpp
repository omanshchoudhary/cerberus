#include "../../include/parser/parser.h"

int main() {
    // assume lexer already produced tokens
    std::vector<Token> tokens = /* your lexer output for "10 + 2 * 3" */;

    Parser parser(tokens);
    Expr* expr = parser.expression();

    printExpr(expr);
}

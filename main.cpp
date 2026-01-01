#include <iostream>
#include "include/ast/expr.h"
#include "include/token.h"
#include "include/interpreter/interpreter.h"
#include "include/lexer/lexer.h"
#include "include/parser/parser.h"

int main() {
    std::string source = "let x = 10 + 2 * 3; print(x);";

    auto tokens = createTokens(source);
    Parser parser(tokens);

    Stmt* stmt1 = parser.parseStatement();
    Stmt* stmt2 = parser.parseStatement();

    execute(stmt1);
    execute(stmt2);

    return 0;
}

#include <iostream>
#include "include/ast/expr.h"
#include "include/token.h"
#include "include/interpreter/interpreter.h"
#include "include/lexer/lexer.h"
#include "include/parser/parser.h"

int main() {
    std::string source = "let x = 10 + 2 * 3; print(x); print(x > 10);";

    auto tokens = createTokens(source);
    Parser parser(tokens);

    auto program  = parser.parseProgram();
    for(auto smt : program){
        execute(smt);
    }

    return 0;
}

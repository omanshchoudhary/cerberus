#include <iostream>
#include <fstream>
#include <sstream>
#include "include/ast/expr.h"
#include "include/token.h"
#include "include/interpreter/interpreter.h"
#include "include/lexer/lexer.h"
#include "include/parser/parser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: cerberus <file.cerb>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    auto tokens = createTokens(source);
    Parser parser(tokens);

    auto program = parser.parseProgram();
    for (auto smt : program) {
        execute(smt);
    }

    return 0;
}

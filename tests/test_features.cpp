#include <iostream>
#include "include/ast/expr.h"
#include "include/token.h"
#include "include/interpreter/interpreter.h"
#include "include/lexer/lexer.h"
#include "include/parser/parser.h"

void testFeature(const std::string& name, const std::string& code) {
    std::cout << "\n=== Testing " << name << " ===" << std::endl;
    std::cout << "Code: " << code << std::endl;
    try {
        auto tokens = createTokens(code);
        Parser parser(tokens);
        auto program = parser.parseProgram();
        for(auto smt : program) {
            execute(smt);
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

int main() {
    testFeature("Variables", "let x = 42; print(x);");
    testFeature("Arithmetic", "let x = 10 + 5 * 2; print(x);");
    testFeature("Comparison", "let x = 10; print(x > 5);");
    testFeature("Parentheses", "let x = (10 + 5) * 2; print(x);");
    
    std::cout << "\n=== Testing Unimplemented Features ===" << std::endl;
    testFeature("If Statement", "let x = 10; if (x > 5) { print(x); }");
    testFeature("While Loop", "let x = 0; while (x < 3) { print(x); let x = x + 1; }");
    testFeature("Division", "let x = 10 / 2; print(x);");
    testFeature("Strings", "print(\"Hello World\");");
    
    return 0;
}

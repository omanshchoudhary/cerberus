#include <iostream>
#include "../../include/ast/expr.h"

void printExpr(Expr* expr){
    if(auto* literal = dynamic_cast<LiteralExpr*>(expr)){
        std::cout<<literal->value;
        return;
    }
    if (auto* variable = dynamic_cast<VariableExpr*>(expr)) {
        std::cout << variable->name;
        return;
    }    
    if(auto* binary = dynamic_cast<BinaryExpr*>(expr)) {
        std::cout<<"(";
        switch (binary->op)
        {
        case TokenType::PLUS: std::cout<<"+"; break;
        case TokenType::STAR: std::cout<<"*"; break;
        default:
            std::cout<<"?";
            break;
        }

        std::cout << " ";
        printExpr(binary->left);
        std::cout << " ";
        printExpr(binary->right);
        std::cout << ")";
        return;
    }
}

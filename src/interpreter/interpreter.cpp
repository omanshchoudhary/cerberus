#include<unordered_map>
#include<stdexcept>
#include "../../include/interpreter/interpreter.h"
#include "../../include/token.h"

int evaluate(Expr* expr){
    if(auto* literal = dynamic_cast<LiteralExpr*>(expr)){
        return literal->value;
    }
    if(auto* binary = dynamic_cast<BinaryExpr*>(expr)){
        int left = evaluate(binary->left);
        int right=evaluate(binary->right);

        switch (binary->op)
        {
        case TokenType::PLUS:  return left + right;
        case TokenType::STAR:  return left * right;
        default:
            throw std::runtime_error("Unsupported binary operator");
        }
    }
    throw std::runtime_error("Unknown expression type");

}
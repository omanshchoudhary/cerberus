#include<unordered_map>
#include<stdexcept>
#include "../../include/interpreter/interpreter.h"
#include "../../include/token.h"

static std::unordered_map<std::string, int> environment;

void defineVariable(const std::string& name, int value) {
    environment[name] = value;
}

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
    if(auto* variable = dynamic_cast<VariableExpr*>(expr)){
        auto it = environment.find(variable->name);
        if(it == environment.end()){
            throw std::runtime_error("Undefined variable: " + variable->name);
        }
        return it->second;
    }
    throw std::runtime_error("Unknown expression type");

}
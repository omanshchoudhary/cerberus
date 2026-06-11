#include "../../include/parser/parser.h"
#include "../../include/ast/expr.h"
#include <stdexcept>  

Parser::Parser(const std::vector<Token>& tokens): tokens(tokens) {}

bool Parser::isAtEnd() const {
    return tokens[current].type==TokenType::EOF_TOKEN;
}

const Token& Parser::peek() const {
    return tokens[current];
}

const Token& Parser::previous() const {
    return tokens[current-1];
}

const Token& Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::check(TokenType type) const {
    if(isAtEnd()) return false;
    return peek().type==type;
}

bool Parser::match(TokenType type){
    if(check(type)){
        advance();
        return true;    
    }
    return false;
}

Expr* Parser::factor(){
    if(match(TokenType::NUMBER)){
        int value = std::stoi(previous().lexeme);
        return new LiteralExpr(value);
    }
    if(match(TokenType::IDENTIFIER)){
        return new VariableExpr(previous().lexeme);
    }
    if (match(TokenType::LPAREN)) {
        Expr* expr = expression();
        if (!match(TokenType::RPAREN)) {
            throw std::runtime_error("Expected ')' after expression");
        }
        return expr;
    }

    throw std::runtime_error("Expected expression but got '" + peek().lexeme + "'");
}

Expr* Parser::term(){
    Expr* expr = factor();

    while(match(TokenType::STAR) || match(TokenType::SLASH)){
        TokenType op = previous().type;
        Expr* right = factor();
        expr= new BinaryExpr(expr, op, right);
    }
    return expr;
}

Expr* Parser::expression(){
    return comparison();
}

Stmt* Parser::parseStatement(){
    if(match(TokenType::LET)){
        return letStatement();
    }
    if(match(TokenType::PRINT)){
        return printStatement();
    }
    return nullptr;
}

Stmt* Parser::letStatement(){
    if (!match(TokenType::IDENTIFIER)) {
        throw std::runtime_error("Expected variable name after 'let'");
    }

    std::string name = previous().lexeme;

    if (!match(TokenType::EQUAL)) {
        throw std::runtime_error("Expected '=' after variable name");
    }

    Expr* initializer = expression();

    if (!match(TokenType::SEMICOLON)) {
        throw std::runtime_error("Expected ';' after expression");
    }

    return new LetStmt(name, initializer);
}

Stmt* Parser::printStatement(){
    if(!match(TokenType::LPAREN)){
        throw std::runtime_error("Expected '(' after 'print'");
    }
    Expr* value = expression();

    if(!match(TokenType::RPAREN)){
        throw std::runtime_error("Expected ')'");
    }

    if (!match(TokenType::SEMICOLON)) {
        throw std::runtime_error("Expected ';' after print statement");
    }

    return new PrintStmt(value);
}
Expr* Parser::comparison() {
    Expr* expr = additive();

    while (match(TokenType::LESS) ||
           match(TokenType::GREATER) ||
           match(TokenType::EQUAL_EQUAL)) {
        TokenType op = previous().type;
        Expr* right = additive();
        expr = new BinaryExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::additive() {
    Expr* expr = term();

    while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
        TokenType op = previous().type;
        Expr* right = term();
        expr = new BinaryExpr(expr, op, right);
    }

    return expr;
}

std::vector<Stmt*> Parser::parseProgram(){
    std::vector<Stmt*> statements;
    while(!isAtEnd()){
        statements.push_back(parseStatement());
    }
    return statements;
}
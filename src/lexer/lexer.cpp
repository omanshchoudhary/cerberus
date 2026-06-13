#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>
#include <unordered_map>
#include "../../include/token.h"
#include<iostream>
#include "../../include/lexer/lexer.h"

static const std::unordered_map<std::string, TokenType> keywords = {
    {"let", TokenType::LET},
    {"print", TokenType::PRINT},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE}
};

static const std::unordered_map<char, TokenType> operators = {
    {'+', TokenType::PLUS},
    {'-', TokenType::MINUS},
    {'*', TokenType::STAR},
    {'/', TokenType::SLASH},
    {'<', TokenType::LESS},
    {'>', TokenType::GREATER},
    {'(', TokenType::LPAREN},
    {')', TokenType::RPAREN},
    {'{', TokenType::LBRACE},
    {'}', TokenType::RBRACE},
    {';', TokenType::SEMICOLON},
    {'=', TokenType::EQUAL}
};


std::vector<Token> createTokens(const std::string& s){
    std::vector<Token> tokens;
    int line = 1;
    for(size_t i =0;i<s.length();i++){
        if(s[i]=='\n') line++;
        if(std::isspace(static_cast<unsigned char>(s[i]))) continue;
        else if(std::isdigit(static_cast<unsigned char>(s[i]))){
            std::string digit;
            while(i<s.length() && std::isdigit(static_cast<unsigned char>(s[i]))){
                digit+=s[i];
                i++;
            }
            tokens.push_back(Token{TokenType::NUMBER, digit, line});
            i--;
        }
        else if(std::isalpha(static_cast<unsigned char>(s[i]))){
            std::string identifier;
            while(i<s.length() && (std::isalnum(static_cast<unsigned char>(s[i])) || s[i] == '_')){
                identifier+=s[i];
                i++;
            }
            if(keywords.find(identifier)!=keywords.end()){
                tokens.push_back(Token{keywords.at(identifier), identifier, line});
            }
            else{
                tokens.push_back(Token{TokenType::IDENTIFIER, identifier,line});

            }
            i--;
        }
        else{  
            char symbol=s[i];
            
            if(operators.find(symbol) != operators.end()){
                if(i + 1 < s.length() && s[i]=='=' && s[i+1]=='='){
                    tokens.push_back(Token{TokenType::EQUAL_EQUAL, "==", line});
                    i++;
                }
                else{
                    tokens.push_back(Token{operators.at(symbol), std::string(1, symbol), line});
                } 
            }
            // Invalid characters to be thrown as error and not skipped 
            else {
                throw std::runtime_error(std::string("Unknown character: ") + symbol + " on line " + std::to_string(line));
            }
        }
    }
    tokens.push_back(Token{TokenType::EOF_TOKEN, "", line});
    return tokens;
}

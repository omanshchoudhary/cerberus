#include <vector>
#include <string>
#include <cctype>
#include "../../include/token.h"
#include<iostream>

std::vector<Token> createTokens(std::string s){
    std::vector<Token> tokens;
    for(int i =0;i<s.length();i++){
        if(s[i]==' ') continue;
        else if(std::isdigit(s[i])){
            std::string digit;
            while(i<s.length() && std::isdigit(s[i])){
                digit+=s[i];
                i++;
            }
            tokens.push_back(Token{TokenType::NUMBER, digit, 1});
            i--;
        }
        else if(std::isalpha(static_cast<unsigned char>(s[i]))){
            std::string identifier;
            while(i<s.length() && (std::isalnum(static_cast<unsigned char>(s[i])) || s[i] == '_')){
                identifier+=s[i];
                i++;
            }
            tokens.push_back(Token{TokenType::IDENTIFIER, identifier,1});
            i--;
        }
    }
    return tokens;
}

int main(){
    auto tokens = createTokens("123 45");
    std::cout << tokens[1].line;
    return 0;
}
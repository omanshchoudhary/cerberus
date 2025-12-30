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
        else if(isalpha(s[i])
    }
    return tokens;
}

int main(){
    auto tokens = createTokens("123 45");
    std::cout << tokens[1].line;
    return 0;
}
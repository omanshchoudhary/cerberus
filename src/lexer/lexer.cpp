#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include "../../include/token.h"
#include<iostream>

std::unordered_map<std::string, TokenType> initKeywords(){
    std::unordered_map<std::string, TokenType> keywords;
    keywords["let"]=TokenType::LET;
    keywords["print"]=TokenType::PRINT;
    keywords["if"]=TokenType::IF;
    keywords["else"]=TokenType::ELSE;
    keywords["while"]=TokenType::WHILE;
    return keywords;
}

std::vector<Token> createTokens(std::string s){
    std::unordered_map<std::string, TokenType> keywords = initKeywords();
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
            if(keywords.find(identifier)!=keywords.end()){
                tokens.push_back(Token{keywords[identifier], identifier, 1});
            }
            else{
                tokens.push_back(Token{TokenType::IDENTIFIER, identifier,1});

            }
            i--;
        }
    }
    return tokens;
}

int main(){
    auto tokens = createTokens("let my_var 42 print while");
    std::cout << tokens[3].lexeme;
    return 0;
}
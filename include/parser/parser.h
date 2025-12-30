#pragma once

#include <vector>
#include "../token.h"

class Parser
{
public:
    explicit Parser(const std::vector<Token> &tokens);

private:
    const std::vector<Token> &tokens;
    int current = 0;
    bool isAtEnd() const;
    const Token& peek() const;
    const Token& previous() const;
    const Token& advance();
};
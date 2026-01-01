#pragma once
#include <string>
#include "../ast/expr.h"

int evaluate(Expr* expr);
void defineVariable(const std::string& name, int value);
